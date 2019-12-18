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
 long ENOTTY ; 
#define  FS_IOC_FSGETXATTR 131 
#define  FS_IOC_FSSETXATTR 130 
#define  FS_IOC_GETFLAGS 129 
#define  FS_IOC_SETFLAGS 128 
 long ovl_ioctl_set_fsflags (struct file*,unsigned int,unsigned long) ; 
 long ovl_ioctl_set_fsxflags (struct file*,unsigned int,unsigned long) ; 
 long ovl_real_ioctl (struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long ovl_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	switch (cmd) {
	case FS_IOC_GETFLAGS:
	case FS_IOC_FSGETXATTR:
		ret = ovl_real_ioctl(file, cmd, arg);
		break;

	case FS_IOC_SETFLAGS:
		ret = ovl_ioctl_set_fsflags(file, cmd, arg);
		break;

	case FS_IOC_FSSETXATTR:
		ret = ovl_ioctl_set_fsxflags(file, cmd, arg);
		break;

	default:
		ret = -ENOTTY;
	}

	return ret;
}