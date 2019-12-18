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
struct perf_event {int /*<<< orphan*/  fasync; } ;
struct inode {int dummy; } ;
struct file {struct perf_event* private_data; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static int perf_fasync(int fd, struct file *filp, int on)
{
	struct inode *inode = file_inode(filp);
	struct perf_event *event = filp->private_data;
	int retval;

	inode_lock(inode);
	retval = fasync_helper(fd, filp, on, &event->fasync);
	inode_unlock(inode);

	if (retval < 0)
		return retval;

	return 0;
}