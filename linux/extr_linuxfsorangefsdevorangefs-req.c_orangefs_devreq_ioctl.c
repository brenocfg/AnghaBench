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
 long check_ioctl_command (unsigned int) ; 
 scalar_t__ dispatch_ioctl_command (unsigned int,unsigned long) ; 

__attribute__((used)) static long orangefs_devreq_ioctl(struct file *file,
			       unsigned int command, unsigned long arg)
{
	long ret;

	/* Check for properly constructed commands */
	ret = check_ioctl_command(command);
	if (ret < 0)
		return (int)ret;

	return (int)dispatch_ioctl_command(command, arg);
}