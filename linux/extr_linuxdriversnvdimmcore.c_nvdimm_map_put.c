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
struct nvdimm_map {int /*<<< orphan*/  kref; struct nvdimm_bus* nvdimm_bus; } ;
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_map_release ; 

__attribute__((used)) static void nvdimm_map_put(void *data)
{
	struct nvdimm_map *nvdimm_map = data;
	struct nvdimm_bus *nvdimm_bus = nvdimm_map->nvdimm_bus;

	nvdimm_bus_lock(&nvdimm_bus->dev);
	kref_put(&nvdimm_map->kref, nvdimm_map_release);
	nvdimm_bus_unlock(&nvdimm_bus->dev);
}