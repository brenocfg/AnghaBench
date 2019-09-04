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
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int sync_inode_metadata (struct inode*,int) ; 

__attribute__((used)) static int exofs_file_fsync(struct file *filp, loff_t start, loff_t end,
			    int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	int ret;

	ret = file_write_and_wait_range(filp, start, end);
	if (ret)
		return ret;

	inode_lock(inode);
	ret = sync_inode_metadata(filp->f_mapping->host, 1);
	inode_unlock(inode);
	return ret;
}