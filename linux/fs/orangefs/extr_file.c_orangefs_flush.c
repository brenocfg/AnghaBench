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
struct inode {int i_state; int /*<<< orphan*/  i_lock; } ;
struct file {TYPE_1__* f_mapping; int /*<<< orphan*/ * private_data; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int I_DIRTY_TIME ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int filemap_write_and_wait_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orangefs_flush(struct file *file, fl_owner_t id)
{
	/*
	 * This is vfs_fsync_range(file, 0, LLONG_MAX, 0) without the
	 * service_operation in orangefs_fsync.
	 *
	 * Do not send fsync to OrangeFS server on a close.  Do send fsync
	 * on an explicit fsync call.  This duplicates historical OrangeFS
	 * behavior.
	 */
	struct inode *inode = file->f_mapping->host;
	int r;

	kfree(file->private_data);
	file->private_data = NULL;

	if (inode->i_state & I_DIRTY_TIME) {
		spin_lock(&inode->i_lock);
		inode->i_state &= ~I_DIRTY_TIME;
		spin_unlock(&inode->i_lock);
		mark_inode_dirty_sync(inode);
	}

	r = filemap_write_and_wait_range(file->f_mapping, 0, LLONG_MAX);
	if (r > 0)
		return 0;
	else
		return r;
}