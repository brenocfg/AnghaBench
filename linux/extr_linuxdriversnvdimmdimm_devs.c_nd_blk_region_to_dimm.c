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
struct nvdimm {int dummy; } ;
struct nd_region {struct nd_mapping* mapping; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;
struct nd_blk_region {struct nd_region nd_region; } ;

/* Variables and functions */

struct nvdimm *nd_blk_region_to_dimm(struct nd_blk_region *ndbr)
{
	struct nd_region *nd_region = &ndbr->nd_region;
	struct nd_mapping *nd_mapping = &nd_region->mapping[0];

	return nd_mapping->nvdimm;
}