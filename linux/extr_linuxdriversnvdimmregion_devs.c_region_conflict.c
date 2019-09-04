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
struct nd_region {scalar_t__ ndr_start; scalar_t__ ndr_size; } ;
struct device {int dummy; } ;
struct conflict_context {scalar_t__ start; scalar_t__ size; struct nd_region* nd_region; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  is_memory (struct device*) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static int region_conflict(struct device *dev, void *data)
{
	struct nd_region *nd_region;
	struct conflict_context *ctx = data;
	resource_size_t res_end, region_end, region_start;

	if (!is_memory(dev))
		return 0;

	nd_region = to_nd_region(dev);
	if (nd_region == ctx->nd_region)
		return 0;

	res_end = ctx->start + ctx->size;
	region_start = nd_region->ndr_start;
	region_end = region_start + nd_region->ndr_size;
	if (ctx->start >= region_start && ctx->start < region_end)
		return -EBUSY;
	if (res_end > region_start && res_end <= region_end)
		return -EBUSY;
	return 0;
}