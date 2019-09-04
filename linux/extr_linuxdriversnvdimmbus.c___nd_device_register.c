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
struct device {struct device* parent; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_schedule_domain (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  nd_async_device_register ; 
 int /*<<< orphan*/  nd_async_domain ; 
 int /*<<< orphan*/  nvdimm_bus_type ; 

void __nd_device_register(struct device *dev)
{
	if (!dev)
		return;
	dev->bus = &nvdimm_bus_type;
	if (dev->parent)
		get_device(dev->parent);
	get_device(dev);
	async_schedule_domain(nd_async_device_register, dev,
			&nd_async_domain);
}