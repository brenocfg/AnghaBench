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
struct nd_region {int /*<<< orphan*/  ns_seed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ND_DEVICE_NAMESPACE_IO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ is_nd_blk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_nvdimm_bus_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd_device_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_namespace_blk_create (struct nd_region*) ; 
 int /*<<< orphan*/  nd_namespace_pmem_create (struct nd_region*) ; 
 scalar_t__ nd_region_to_nstype (struct nd_region*) ; 

void nd_region_create_ns_seed(struct nd_region *nd_region)
{
	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));

	if (nd_region_to_nstype(nd_region) == ND_DEVICE_NAMESPACE_IO)
		return;

	if (is_nd_blk(&nd_region->dev))
		nd_region->ns_seed = nd_namespace_blk_create(nd_region);
	else
		nd_region->ns_seed = nd_namespace_pmem_create(nd_region);

	/*
	 * Seed creation failures are not fatal, provisioning is simply
	 * disabled until memory becomes available
	 */
	if (!nd_region->ns_seed)
		dev_err(&nd_region->dev, "failed to create %s namespace\n",
				is_nd_blk(&nd_region->dev) ? "blk" : "pmem");
	else
		nd_device_register(nd_region->ns_seed);
}