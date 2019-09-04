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
struct file {int dummy; } ;

/* Variables and functions */
 long F_UNLCK ; 
 int do_fcntl_add_lease (unsigned int,struct file*,long) ; 
 int vfs_setlease (struct file*,long,int /*<<< orphan*/ *,void**) ; 

int fcntl_setlease(unsigned int fd, struct file *filp, long arg)
{
	if (arg == F_UNLCK)
		return vfs_setlease(filp, F_UNLCK, NULL, (void **)&filp);
	return do_fcntl_add_lease(fd, filp, arg);
}