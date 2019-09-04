#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {int f_pos; struct dentry* private_data; TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_child; int /*<<< orphan*/  d_subdirs; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  inode_lock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_cursor (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* next_positive (struct dentry*,int /*<<< orphan*/ *,int) ; 

loff_t dcache_dir_lseek(struct file *file, loff_t offset, int whence)
{
	struct dentry *dentry = file->f_path.dentry;
	switch (whence) {
		case 1:
			offset += file->f_pos;
		case 0:
			if (offset >= 0)
				break;
		default:
			return -EINVAL;
	}
	if (offset != file->f_pos) {
		file->f_pos = offset;
		if (file->f_pos >= 2) {
			struct dentry *cursor = file->private_data;
			struct dentry *to;
			loff_t n = file->f_pos - 2;

			inode_lock_shared(dentry->d_inode);
			to = next_positive(dentry, &dentry->d_subdirs, n);
			move_cursor(cursor, to ? &to->d_child : NULL);
			inode_unlock_shared(dentry->d_inode);
		}
	}
	return offset;
}