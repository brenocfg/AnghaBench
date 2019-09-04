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
struct device {int dummy; } ;

/* Variables and functions */

int register_xen_selfballooning(struct device *dev)
{
	int error = -1;

#ifdef CONFIG_SYSFS
	error = sysfs_create_group(&dev->kobj, &selfballoon_group);
#endif
	return error;
}