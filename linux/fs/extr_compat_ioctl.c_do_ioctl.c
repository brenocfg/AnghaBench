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
 int security_file_ioctl (struct file*,unsigned int,unsigned long) ; 
 int vfs_ioctl (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static int do_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int err;

	err = security_file_ioctl(file, cmd, arg);
	if (err)
		return err;

	return vfs_ioctl(file, cmd, arg);
}