#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvdimm_drvdata {int dummy; } ;
struct nvdimm_bus {int dummy; } ;
struct nvdimm {int /*<<< orphan*/  busy; } ;
struct nd_region {int ndr_mappings; struct device* ns_seed; struct device* dax_seed; struct device* pfn_seed; struct device* btt_seed; struct nd_mapping* mapping; } ;
struct nd_pfn {TYPE_2__* ndns; } ;
struct nd_mapping {struct nvdimm_drvdata* ndd; int /*<<< orphan*/  lock; struct nvdimm* nvdimm; } ;
struct TYPE_8__ {TYPE_3__* ndns; } ;
struct nd_dax {TYPE_4__ nd_pfn; } ;
struct nd_btt {TYPE_1__* ndns; } ;
struct device {struct device* parent; } ;
struct TYPE_7__ {struct device dev; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 scalar_t__ is_nd_region (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_mapping_free_labels (struct nd_mapping*) ; 
 int /*<<< orphan*/  nd_region_create_btt_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_create_dax_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_create_ns_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nd_region_create_pfn_seed (struct nd_region*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  put_ndd (struct nvdimm_drvdata*) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_dax* to_nd_dax (struct device*) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static void nd_region_notify_driver_action(struct nvdimm_bus *nvdimm_bus,
		struct device *dev, bool probe)
{
	struct nd_region *nd_region;

	if (!probe && is_nd_region(dev)) {
		int i;

		nd_region = to_nd_region(dev);
		for (i = 0; i < nd_region->ndr_mappings; i++) {
			struct nd_mapping *nd_mapping = &nd_region->mapping[i];
			struct nvdimm_drvdata *ndd = nd_mapping->ndd;
			struct nvdimm *nvdimm = nd_mapping->nvdimm;

			mutex_lock(&nd_mapping->lock);
			nd_mapping_free_labels(nd_mapping);
			mutex_unlock(&nd_mapping->lock);

			put_ndd(ndd);
			nd_mapping->ndd = NULL;
			if (ndd)
				atomic_dec(&nvdimm->busy);
		}
	}
	if (dev->parent && is_nd_region(dev->parent) && probe) {
		nd_region = to_nd_region(dev->parent);
		nvdimm_bus_lock(dev);
		if (nd_region->ns_seed == dev)
			nd_region_create_ns_seed(nd_region);
		nvdimm_bus_unlock(dev);
	}
	if (is_nd_btt(dev) && probe) {
		struct nd_btt *nd_btt = to_nd_btt(dev);

		nd_region = to_nd_region(dev->parent);
		nvdimm_bus_lock(dev);
		if (nd_region->btt_seed == dev)
			nd_region_create_btt_seed(nd_region);
		if (nd_region->ns_seed == &nd_btt->ndns->dev)
			nd_region_create_ns_seed(nd_region);
		nvdimm_bus_unlock(dev);
	}
	if (is_nd_pfn(dev) && probe) {
		struct nd_pfn *nd_pfn = to_nd_pfn(dev);

		nd_region = to_nd_region(dev->parent);
		nvdimm_bus_lock(dev);
		if (nd_region->pfn_seed == dev)
			nd_region_create_pfn_seed(nd_region);
		if (nd_region->ns_seed == &nd_pfn->ndns->dev)
			nd_region_create_ns_seed(nd_region);
		nvdimm_bus_unlock(dev);
	}
	if (is_nd_dax(dev) && probe) {
		struct nd_dax *nd_dax = to_nd_dax(dev);

		nd_region = to_nd_region(dev->parent);
		nvdimm_bus_lock(dev);
		if (nd_region->dax_seed == dev)
			nd_region_create_dax_seed(nd_region);
		if (nd_region->ns_seed == &nd_dax->nd_pfn.ndns->dev)
			nd_region_create_ns_seed(nd_region);
		nvdimm_bus_unlock(dev);
	}
}