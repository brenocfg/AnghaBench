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
struct nvdimm_bus {int /*<<< orphan*/  reconfig_mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

void nvdimm_bus_unlock(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	if (!nvdimm_bus)
		return;
	mutex_unlock(&nvdimm_bus->reconfig_mutex);
}