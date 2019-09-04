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
 long ENOIOCTLCMD ; 
#define  FS_IOC32_GETFLAGS 129 
#define  FS_IOC32_SETFLAGS 128 
 unsigned int FS_IOC_GETFLAGS ; 
 unsigned int FS_IOC_SETFLAGS ; 
 long ovl_ioctl (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long ovl_compat_ioctl(struct file *file, unsigned int cmd,
			     unsigned long arg)
{
	switch (cmd) {
	case FS_IOC32_GETFLAGS:
		cmd = FS_IOC_GETFLAGS;
		break;

	case FS_IOC32_SETFLAGS:
		cmd = FS_IOC_SETFLAGS;
		break;

	default:
		return -ENOIOCTLCMD;
	}

	return ovl_ioctl(file, cmd, arg);
}