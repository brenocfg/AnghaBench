#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {void* base; } ;
struct nfit_blk_mmio {TYPE_1__ addr; } ;
struct nfit_blk {struct nfit_blk_mmio* mmio; } ;
struct nd_region {int dummy; } ;
struct nd_blk_region {struct nd_region nd_region; struct nfit_blk* blk_provider_data; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 size_t BDW ; 
 int /*<<< orphan*/  arch_invalidate_pmem (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 unsigned int nd_region_acquire_lane (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_release_lane (struct nd_region*,unsigned int) ; 

__attribute__((used)) static int nfit_test_blk_do_io(struct nd_blk_region *ndbr, resource_size_t dpa,
		void *iobuf, u64 len, int rw)
{
	struct nfit_blk *nfit_blk = ndbr->blk_provider_data;
	struct nfit_blk_mmio *mmio = &nfit_blk->mmio[BDW];
	struct nd_region *nd_region = &ndbr->nd_region;
	unsigned int lane;

	lane = nd_region_acquire_lane(nd_region);
	if (rw)
		memcpy(mmio->addr.base + dpa, iobuf, len);
	else {
		memcpy(iobuf, mmio->addr.base + dpa, len);

		/* give us some some coverage of the arch_invalidate_pmem() API */
		arch_invalidate_pmem(mmio->addr.base + dpa, len);
	}
	nd_region_release_lane(nd_region, lane);

	return 0;
}