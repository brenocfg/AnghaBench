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
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_child; int /*<<< orphan*/  d_subdirs; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dentry* scan_positives (struct dentry*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

loff_t dcache_dir_lseek(struct file *file, loff_t offset, int whence)
{
	struct dentry *dentry = file->f_path.dentry;
	switch (whence) {
		case 1:
			offset += file->f_pos;
			/* fall through */
		case 0:
			if (offset >= 0)
				break;
			/* fall through */
		default:
			return -EINVAL;
	}
	if (offset != file->f_pos) {
		struct dentry *cursor = file->private_data;
		struct dentry *to = NULL;

		inode_lock_shared(dentry->d_inode);

		if (offset > 2)
			to = scan_positives(cursor, &dentry->d_subdirs,
					    offset - 2, NULL);
		spin_lock(&dentry->d_lock);
		if (to)
			list_move(&cursor->d_child, &to->d_child);
		else
			list_del_init(&cursor->d_child);
		spin_unlock(&dentry->d_lock);
		dput(to);

		file->f_pos = offset;

		inode_unlock_shared(dentry->d_inode);
	}
	return offset;
}