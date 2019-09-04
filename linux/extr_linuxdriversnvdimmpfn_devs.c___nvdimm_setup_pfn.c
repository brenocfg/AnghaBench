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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct vmem_altmap {scalar_t__ alloc; int /*<<< orphan*/  free; int /*<<< orphan*/  end; scalar_t__ start; int /*<<< orphan*/  reserve; int /*<<< orphan*/  base_pfn; } ;
struct resource {scalar_t__ alloc; int /*<<< orphan*/  free; int /*<<< orphan*/  end; scalar_t__ start; int /*<<< orphan*/  reserve; int /*<<< orphan*/  base_pfn; } ;
struct nd_pfn_sb {int /*<<< orphan*/  npfns; int /*<<< orphan*/  end_trunc; int /*<<< orphan*/  start_pad; int /*<<< orphan*/  dataoff; } ;
struct nd_pfn {scalar_t__ mode; void* npfns; struct nd_pfn_sb* pfn_sb; int /*<<< orphan*/  dev; struct nd_namespace_common* ndns; } ;
struct nd_namespace_io {struct vmem_altmap res; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct dev_pagemap {int altmap_valid; struct vmem_altmap altmap; struct vmem_altmap res; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PFN_MODE_PMEM ; 
 scalar_t__ PFN_MODE_RAM ; 
 void* PFN_SECTION_ALIGN_UP (scalar_t__) ; 
 int /*<<< orphan*/  PHYS_PFN (scalar_t__) ; 
 scalar_t__ SZ_8K ; 
 scalar_t__ __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,void*,void*) ; 
 int /*<<< orphan*/  init_altmap_base (scalar_t__) ; 
 int /*<<< orphan*/  init_altmap_reserve (scalar_t__) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct vmem_altmap*,struct vmem_altmap*,int) ; 
 scalar_t__ resource_size (struct vmem_altmap*) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __nvdimm_setup_pfn(struct nd_pfn *nd_pfn, struct dev_pagemap *pgmap)
{
	struct resource *res = &pgmap->res;
	struct vmem_altmap *altmap = &pgmap->altmap;
	struct nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
	u64 offset = le64_to_cpu(pfn_sb->dataoff);
	u32 start_pad = __le32_to_cpu(pfn_sb->start_pad);
	u32 end_trunc = __le32_to_cpu(pfn_sb->end_trunc);
	struct nd_namespace_common *ndns = nd_pfn->ndns;
	struct nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	resource_size_t base = nsio->res.start + start_pad;
	struct vmem_altmap __altmap = {
		.base_pfn = init_altmap_base(base),
		.reserve = init_altmap_reserve(base),
	};

	memcpy(res, &nsio->res, sizeof(*res));
	res->start += start_pad;
	res->end -= end_trunc;

	if (nd_pfn->mode == PFN_MODE_RAM) {
		if (offset < SZ_8K)
			return -EINVAL;
		nd_pfn->npfns = le64_to_cpu(pfn_sb->npfns);
		pgmap->altmap_valid = false;
	} else if (nd_pfn->mode == PFN_MODE_PMEM) {
		nd_pfn->npfns = PFN_SECTION_ALIGN_UP((resource_size(res)
					- offset) / PAGE_SIZE);
		if (le64_to_cpu(nd_pfn->pfn_sb->npfns) > nd_pfn->npfns)
			dev_info(&nd_pfn->dev,
					"number of pfns truncated from %lld to %ld\n",
					le64_to_cpu(nd_pfn->pfn_sb->npfns),
					nd_pfn->npfns);
		memcpy(altmap, &__altmap, sizeof(*altmap));
		altmap->free = PHYS_PFN(offset - SZ_8K);
		altmap->alloc = 0;
		pgmap->altmap_valid = true;
	} else
		return -ENXIO;

	return 0;
}