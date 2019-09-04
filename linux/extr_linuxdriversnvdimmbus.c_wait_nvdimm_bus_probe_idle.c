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
struct nvdimm_bus {scalar_t__ probe_active; int /*<<< orphan*/  dev; int /*<<< orphan*/  probe_wait; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

void wait_nvdimm_bus_probe_idle(struct device *dev)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	do {
		if (nvdimm_bus->probe_active == 0)
			break;
		nvdimm_bus_unlock(&nvdimm_bus->dev);
		wait_event(nvdimm_bus->probe_wait,
				nvdimm_bus->probe_active == 0);
		nvdimm_bus_lock(&nvdimm_bus->dev);
	} while (true);
}