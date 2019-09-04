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
struct nd_region {int /*<<< orphan*/  dev; int /*<<< orphan*/  pfn_seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_pfn_create (struct nd_region*) ; 

void nd_region_create_pfn_seed(struct nd_region *nd_region)
{
	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));
	nd_region->pfn_seed = nd_pfn_create(nd_region);
	/*
	 * Seed creation failures are not fatal, provisioning is simply
	 * disabled until memory becomes available
	 */
	if (!nd_region->pfn_seed)
		dev_err(&nd_region->dev, "failed to create pfn namespace\n");
}