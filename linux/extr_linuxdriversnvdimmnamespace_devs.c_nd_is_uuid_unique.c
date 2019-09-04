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
typedef  int /*<<< orphan*/  u8 ;
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_namespace_uuid_busy ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

bool nd_is_uuid_unique(struct device *dev, u8 *uuid)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	if (!nvdimm_bus)
		return false;
	WARN_ON_ONCE(!is_nvdimm_bus_locked(&nvdimm_bus->dev));
	if (device_for_each_child(&nvdimm_bus->dev, uuid,
				is_namespace_uuid_busy) != 0)
		return false;
	return true;
}