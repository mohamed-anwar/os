#ifndef _VFS_H
#define _VFS_H

typedef struct filesystem_struct fs_t;
typedef enum { FS_DIR, FS_FILE } inode_type; 
typedef struct inode_struct inode_t;
typedef struct dentry_struct dentry_t;
typedef struct file_struct file_t;

typedef struct filesystem_struct
{
	uint8_t *name;
	inode_t* (*load)(void*);
	file_t* (*open)(inode_t*);
	void (*read)(void*, uint32_t, file_t*);
}fs_t;

struct inode_struct
{
	uint8_t		*name;
	uint32_t	size;
	inode_type	type;
	inode_t 	*parent;
	dentry_t	*list;
	fs_t		*fs;
	void		*p;	// To be used by filesystem handler
	
	inode_t		*next;	// For directories
};

struct dentry_struct
{
	uint32_t count;
	inode_t *head;
};

struct file_struct
{
	uint32_t pos;
	uint32_t size;
	uint8_t *buf;
};

extern inode_t *vfs_root;
inode_t *vfs_trace_path(inode_t*, uint8_t*);
inode_t *vfs_create(inode_t*, uint8_t*, inode_t*);
void vfs_tree(inode_t*);

void vfs_read(void*, uint32_t, file_t*);
file_t *vfs_fopen(uint8_t*, uint8_t*);

#endif
