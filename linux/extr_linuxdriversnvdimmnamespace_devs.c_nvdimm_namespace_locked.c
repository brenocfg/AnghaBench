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
struct nvdimm {int /*<<< orphan*/  flags; } ;
struct nd_region {int ndr_mappings; struct nd_mapping* mapping; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct nd_namespace_common {struct device dev; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDD_LOCKED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_name (struct nvdimm*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

bool nvdimm_namespace_locked(struct nd_namespace_common *ndns)
{
	int i;
	bool locked = false;
	struct device *dev = &ndns->dev;
	struct nd_region *nd_region = to_nd_region(dev->parent);

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm *nvdimm = nd_mapping->nvdimm;

		if (test_bit(NDD_LOCKED, &nvdimm->flags)) {
			dev_dbg(dev, "%s locked\n", nvdimm_name(nvdimm));
			locked = true;
		}
	}
	return locked;
}