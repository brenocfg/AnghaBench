#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct nd_device_driver {int /*<<< orphan*/  (* shutdown ) (struct device*) ;} ;
struct device {TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 struct nd_device_driver* to_nd_device_driver (TYPE_1__*) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

__attribute__((used)) static void nvdimm_bus_shutdown(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	struct nd_device_driver *nd_drv = NULL;

	if (dev->driver)
		nd_drv = to_nd_device_driver(dev->driver);

	if (nd_drv && nd_drv->shutdown) {
		nd_drv->shutdown(dev);
		dev_dbg(&nvdimm_bus->dev, "%s.shutdown(%s)\n",
				dev->driver->name, dev_name(dev));
	}
}