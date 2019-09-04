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
struct nvdimm_bus {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (struct device*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvdimm_bus*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_class ; 
 int /*<<< orphan*/  nvdimm_bus_major ; 

int nvdimm_bus_create_ndctl(struct nvdimm_bus *nvdimm_bus)
{
	dev_t devt = MKDEV(nvdimm_bus_major, nvdimm_bus->id);
	struct device *dev;

	dev = device_create(nd_class, &nvdimm_bus->dev, devt, nvdimm_bus,
			"ndctl%d", nvdimm_bus->id);

	if (IS_ERR(dev))
		dev_dbg(&nvdimm_bus->dev, "failed to register ndctl%d: %ld\n",
				nvdimm_bus->id, PTR_ERR(dev));
	return PTR_ERR_OR_ZERO(dev);
}