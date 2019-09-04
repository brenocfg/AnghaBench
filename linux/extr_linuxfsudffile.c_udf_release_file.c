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
struct inode {int /*<<< orphan*/  i_writecount; } ;
struct file {int f_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 TYPE_1__* UDF_I (struct inode*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  udf_discard_prealloc (struct inode*) ; 
 int /*<<< orphan*/  udf_truncate_tail_extent (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_release_file(struct inode *inode, struct file *filp)
{
	if (filp->f_mode & FMODE_WRITE &&
	    atomic_read(&inode->i_writecount) == 1) {
		/*
		 * Grab i_mutex to avoid races with writes changing i_size
		 * while we are running.
		 */
		inode_lock(inode);
		down_write(&UDF_I(inode)->i_data_sem);
		udf_discard_prealloc(inode);
		udf_truncate_tail_extent(inode);
		up_write(&UDF_I(inode)->i_data_sem);
		inode_unlock(inode);
	}
	return 0;
}