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
struct region_search_spa {scalar_t__ addr; struct nd_region* region; } ;
struct nd_region {scalar_t__ ndr_start; scalar_t__ ndr_size; } ;
struct device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_region_device (struct device*) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static int nfit_test_search_region_spa(struct device *dev, void *data)
{
	struct region_search_spa *ctx = data;
	struct nd_region *nd_region;
	resource_size_t ndr_end;

	if (!is_region_device(dev))
		return 0;

	nd_region = to_nd_region(dev);
	ndr_end = nd_region->ndr_start + nd_region->ndr_size;

	if (ctx->addr >= nd_region->ndr_start && ctx->addr < ndr_end) {
		ctx->region = nd_region;
		return 1;
	}

	return 0;
}