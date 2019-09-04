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
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct nd_namespace_common {TYPE_1__ dev; int /*<<< orphan*/  rw_bytes; } ;
struct nd_namespace_io {int /*<<< orphan*/  addr; struct resource res; int /*<<< orphan*/  bb; int /*<<< orphan*/  size; struct nd_namespace_common common; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_MEMREMAP_PMEM ; 
 int EBUSY ; 
 int ENOMEM ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,struct resource*) ; 
 scalar_t__ devm_init_badblocks (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_memremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsio_rw_bytes ; 
 int /*<<< orphan*/  nvdimm_badblocks_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  to_nd_region (int /*<<< orphan*/ ) ; 

int devm_nsio_enable(struct device *dev, struct nd_namespace_io *nsio)
{
	struct resource *res = &nsio->res;
	struct nd_namespace_common *ndns = &nsio->common;

	nsio->size = resource_size(res);
	if (!devm_request_mem_region(dev, res->start, resource_size(res),
				dev_name(&ndns->dev))) {
		dev_warn(dev, "could not reserve region %pR\n", res);
		return -EBUSY;
	}

	ndns->rw_bytes = nsio_rw_bytes;
	if (devm_init_badblocks(dev, &nsio->bb))
		return -ENOMEM;
	nvdimm_badblocks_populate(to_nd_region(ndns->dev.parent), &nsio->bb,
			&nsio->res);

	nsio->addr = devm_memremap(dev, res->start, resource_size(res),
			ARCH_MEMREMAP_PMEM);

	return PTR_ERR_OR_ZERO(nsio->addr);
}