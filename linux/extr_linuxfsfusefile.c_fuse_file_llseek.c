#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  SEEK_CUR 132 
#define  SEEK_DATA 131 
#define  SEEK_END 130 
#define  SEEK_HOLE 129 
#define  SEEK_SET 128 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_lseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_update_attributes (struct inode*,struct file*) ; 
 int /*<<< orphan*/  generic_file_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static loff_t fuse_file_llseek(struct file *file, loff_t offset, int whence)
{
	loff_t retval;
	struct inode *inode = file_inode(file);

	switch (whence) {
	case SEEK_SET:
	case SEEK_CUR:
		 /* No i_mutex protection necessary for SEEK_CUR and SEEK_SET */
		retval = generic_file_llseek(file, offset, whence);
		break;
	case SEEK_END:
		inode_lock(inode);
		retval = fuse_update_attributes(inode, file);
		if (!retval)
			retval = generic_file_llseek(file, offset, whence);
		inode_unlock(inode);
		break;
	case SEEK_HOLE:
	case SEEK_DATA:
		inode_lock(inode);
		retval = fuse_lseek(file, offset, whence);
		inode_unlock(inode);
		break;
	default:
		retval = -EINVAL;
	}

	return retval;
}