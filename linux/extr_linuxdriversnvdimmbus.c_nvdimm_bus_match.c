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
struct nd_device_driver {int /*<<< orphan*/  type; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_nvdimm_bus (struct device*) ; 
 struct nd_device_driver nd_bus_driver ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nd_device_driver* to_nd_device_driver (struct device_driver*) ; 
 int /*<<< orphan*/  to_nd_device_type (struct device*) ; 

__attribute__((used)) static int nvdimm_bus_match(struct device *dev, struct device_driver *drv)
{
	struct nd_device_driver *nd_drv = to_nd_device_driver(drv);

	if (is_nvdimm_bus(dev) && nd_drv == &nd_bus_driver)
		return true;

	return !!test_bit(to_nd_device_type(dev), &nd_drv->type);
}