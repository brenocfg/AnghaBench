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
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long ENODEV ; 
 long ENOTTY ; 
 long EPERM ; 
#define  IOCTL_XENBUS_BACKEND_EVTCHN 129 
#define  IOCTL_XENBUS_BACKEND_SETUP 128 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 long xen_store_evtchn ; 
 long xenbus_alloc (unsigned long) ; 

__attribute__((used)) static long xenbus_backend_ioctl(struct file *file, unsigned int cmd,
				 unsigned long data)
{
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	switch (cmd) {
	case IOCTL_XENBUS_BACKEND_EVTCHN:
		if (xen_store_evtchn > 0)
			return xen_store_evtchn;
		return -ENODEV;
	case IOCTL_XENBUS_BACKEND_SETUP:
		return xenbus_alloc(data);
	default:
		return -ENOTTY;
	}
}