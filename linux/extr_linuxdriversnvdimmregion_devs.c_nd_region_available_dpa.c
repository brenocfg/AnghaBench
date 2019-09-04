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
struct nvdimm_drvdata {int dummy; } ;
struct nd_region {int ndr_mappings; int /*<<< orphan*/  dev; struct nd_mapping* mapping; } ;
struct nd_mapping {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ is_nd_blk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ nd_blk_available_dpa (struct nd_region*) ; 
 scalar_t__ nd_pmem_available_dpa (struct nd_region*,struct nd_mapping*,scalar_t__*) ; 
 struct nvdimm_drvdata* to_ndd (struct nd_mapping*) ; 

resource_size_t nd_region_available_dpa(struct nd_region *nd_region)
{
	resource_size_t blk_max_overlap = 0, available, overlap;
	int i;

	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));

 retry:
	available = 0;
	overlap = blk_max_overlap;
	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);

		/* if a dimm is disabled the available capacity is zero */
		if (!ndd)
			return 0;

		if (is_memory(&nd_region->dev)) {
			available += nd_pmem_available_dpa(nd_region,
					nd_mapping, &overlap);
			if (overlap > blk_max_overlap) {
				blk_max_overlap = overlap;
				goto retry;
			}
		} else if (is_nd_blk(&nd_region->dev))
			available += nd_blk_available_dpa(nd_region);
	}

	return available;
}