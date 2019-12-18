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
struct usbdevfs_ioctl {int ifno; unsigned int ioctl_code; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBDEVFS_IOCTL ; 
 int ioctl (int,int /*<<< orphan*/ ,struct usbdevfs_ioctl*) ; 

__attribute__((used)) static int
usbdev_ioctl (int fd, int ifno, unsigned request, void *param)
{
	struct usbdevfs_ioctl	wrapper;

	wrapper.ifno = ifno;
	wrapper.ioctl_code = request;
	wrapper.data = param;

	return ioctl (fd, USBDEVFS_IOCTL, &wrapper);
}