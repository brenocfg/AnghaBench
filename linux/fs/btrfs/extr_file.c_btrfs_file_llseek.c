#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_maxbytes; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int ENXIO ; 
#define  SEEK_CUR 131 
#define  SEEK_DATA 130 
#define  SEEK_END 129 
#define  SEEK_HOLE 128 
 int find_desired_extent (struct inode*,int*,int) ; 
 int generic_file_llseek (struct file*,int,int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int vfs_setpos (struct file*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t btrfs_file_llseek(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	int ret;

	inode_lock(inode);
	switch (whence) {
	case SEEK_END:
	case SEEK_CUR:
		offset = generic_file_llseek(file, offset, whence);
		goto out;
	case SEEK_DATA:
	case SEEK_HOLE:
		if (offset >= i_size_read(inode)) {
			inode_unlock(inode);
			return -ENXIO;
		}

		ret = find_desired_extent(inode, &offset, whence);
		if (ret) {
			inode_unlock(inode);
			return ret;
		}
	}

	offset = vfs_setpos(file, offset, inode->i_sb->s_maxbytes);
out:
	inode_unlock(inode);
	return offset;
}