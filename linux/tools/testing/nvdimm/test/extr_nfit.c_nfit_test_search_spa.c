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
typedef  scalar_t__ u64 ;
struct region_search_spa {scalar_t__ addr; struct nd_region* region; } ;
struct nvdimm_bus {int /*<<< orphan*/  dev; } ;
struct nvdimm {size_t id; } ;
struct nd_region {int ndr_mappings; struct nd_mapping* mapping; scalar_t__ ndr_start; } ;
struct nd_mapping {struct nvdimm* nvdimm; } ;
struct nd_cmd_translate_spa {int num_nvdimms; TYPE_1__* devices; scalar_t__ spa; } ;
struct TYPE_2__ {scalar_t__ dpa; int /*<<< orphan*/  nfit_device_handle; } ;

/* Variables and functions */
 int ENODEV ; 
 int device_for_each_child (int /*<<< orphan*/ *,struct region_search_spa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * handle ; 
 int /*<<< orphan*/  nfit_test_search_region_spa ; 

__attribute__((used)) static int nfit_test_search_spa(struct nvdimm_bus *bus,
		struct nd_cmd_translate_spa *spa)
{
	int ret;
	struct nd_region *nd_region = NULL;
	struct nvdimm *nvdimm = NULL;
	struct nd_mapping *nd_mapping = NULL;
	struct region_search_spa ctx = {
		.addr = spa->spa,
		.region = NULL,
	};
	u64 dpa;

	ret = device_for_each_child(&bus->dev, &ctx,
				nfit_test_search_region_spa);

	if (!ret)
		return -ENODEV;

	nd_region = ctx.region;

	dpa = ctx.addr - nd_region->ndr_start;

	/*
	 * last dimm is selected for test
	 */
	nd_mapping = &nd_region->mapping[nd_region->ndr_mappings - 1];
	nvdimm = nd_mapping->nvdimm;

	spa->devices[0].nfit_device_handle = handle[nvdimm->id];
	spa->num_nvdimms = 1;
	spa->devices[0].dpa = dpa;

	return 0;
}