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
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_2__* HOSTFS_I (struct inode*) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsync_file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static int hostfs_fsync(struct file *file, loff_t start, loff_t end,
			int datasync)
{
	struct inode *inode = file->f_mapping->host;
	int ret;

	ret = file_write_and_wait_range(file, start, end);
	if (ret)
		return ret;

	inode_lock(inode);
	ret = fsync_file(HOSTFS_I(inode)->fd, datasync);
	inode_unlock(inode);

	return ret;
}