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
struct nvdimm {scalar_t__ num_flush; } ;
struct nd_region {int ndr_mappings; struct nd_mapping* mapping; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_HAS_PMEM_API ; 
 int ENXIO ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 

int nvdimm_has_flush(struct nd_region *nd_region)
{
	int i;

	/* no nvdimm or pmem api == flushing capability unknown */
	if (nd_region->ndr_mappings == 0
			|| !IS_ENABLED(CONFIG_ARCH_HAS_PMEM_API))
		return -ENXIO;

	for (i = 0; i < nd_region->ndr_mappings; i++) {
		struct nd_mapping *nd_mapping = &nd_region->mapping[i];
		struct nvdimm *nvdimm = nd_mapping->nvdimm;

		/* flush hints present / available */
		if (nvdimm->num_flush)
			return 1;
	}

	/*
	 * The platform defines dimm devices without hints, assume
	 * platform persistence mechanism like ADR
	 */
	return 0;
}