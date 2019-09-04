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
struct nvdimm_map {void* mem; int /*<<< orphan*/  kref; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 struct nvdimm_map* alloc_nvdimm_map (struct device*,int /*<<< orphan*/ ,size_t,unsigned long) ; 
 scalar_t__ devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct nvdimm_map*) ; 
 struct nvdimm_map* find_nvdimm_map (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_map_put ; 

void *devm_nvdimm_memremap(struct device *dev, resource_size_t offset,
		size_t size, unsigned long flags)
{
	struct nvdimm_map *nvdimm_map;

	nvdimm_bus_lock(dev);
	nvdimm_map = find_nvdimm_map(dev, offset);
	if (!nvdimm_map)
		nvdimm_map = alloc_nvdimm_map(dev, offset, size, flags);
	else
		kref_get(&nvdimm_map->kref);
	nvdimm_bus_unlock(dev);

	if (!nvdimm_map)
		return NULL;

	if (devm_add_action_or_reset(dev, nvdimm_map_put, nvdimm_map))
		return NULL;

	return nvdimm_map->mem;
}