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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int TW_IOCTL_ERROR_OS_ENODEV ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 unsigned int iminor (struct inode*) ; 
 unsigned int twa_device_extension_count ; 

__attribute__((used)) static int twa_chrdev_open(struct inode *inode, struct file *file)
{
	unsigned int minor_number;
	int retval = TW_IOCTL_ERROR_OS_ENODEV;

	if (!capable(CAP_SYS_ADMIN)) {
		retval = -EACCES;
		goto out;
	}

	minor_number = iminor(inode);
	if (minor_number >= twa_device_extension_count)
		goto out;
	retval = 0;
out:
	return retval;
}