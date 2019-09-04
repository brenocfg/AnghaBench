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
struct nvdimm_bus {int dummy; } ;
struct nd_region {int ndr_mappings; int /*<<< orphan*/  dev; struct nd_mapping* mapping; } ;
struct nd_mapping {int dummy; } ;
struct nd_label_id {int /*<<< orphan*/  id; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  dev_WARN_ONCE (int /*<<< orphan*/ *,scalar_t__,char*,scalar_t__,unsigned long long) ; 
 int merge_dpa (struct nd_region*,struct nd_mapping*,struct nd_label_id*) ; 
 int /*<<< orphan*/  release_free_pmem (struct nvdimm_bus*,struct nd_mapping*) ; 
 int reserve_free_pmem (struct nvdimm_bus*,struct nd_mapping*) ; 
 scalar_t__ scan_allocate (struct nd_region*,struct nd_mapping*,struct nd_label_id*,scalar_t__) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grow_dpa_allocation(struct nd_region *nd_region,
		struct nd_label_id *label_id, resource_size_t n)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);
	bool is_pmem = strncmp(label_id->id, "pmem", 4) == 0;
	int i;

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		resource_size_t rem = n;
		int rc, j;

		/*
		 * In the BLK case try once with all unallocated PMEM
		 * reserved, and once without
		 */
		for (j = is_pmem; j < 2; j++) {
			bool blk_only = j == 0;

			if (blk_only) {
				rc = reserve_free_pmem(nvdimm_bus, nd_mapping);
				if (rc)
					return rc;
			}
			rem = scan_allocate(nd_region, nd_mapping,
					label_id, rem);
			if (blk_only)
				release_free_pmem(nvdimm_bus, nd_mapping);

			/* try again and allow encroachments into PMEM */
			if (rem == 0)
				break;
		}

		dev_WARN_ONCE(&nd_region->dev, rem,
				"allocation underrun: %#llx of %#llx bytes\n",
				(unsigned long long) n - rem,
				(unsigned long long) n);
		if (rem)
			return -ENXIO;

		rc = merge_dpa(nd_region, nd_mapping, label_id);
		if (rc)
			return rc;
	}

	return 0;
}