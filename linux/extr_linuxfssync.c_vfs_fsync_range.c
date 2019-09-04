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
struct inode {int i_state; } ;
struct file {TYPE_2__* f_op; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int (* fsync ) (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EINVAL ; 
 int I_DIRTY_TIME ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 
 int stub1 (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int vfs_fsync_range(struct file *file, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = file->f_mapping->host;

	if (!file->f_op->fsync)
		return -EINVAL;
	if (!datasync && (inode->i_state & I_DIRTY_TIME))
		mark_inode_dirty_sync(inode);
	return file->f_op->fsync(file, start, end, datasync);
}