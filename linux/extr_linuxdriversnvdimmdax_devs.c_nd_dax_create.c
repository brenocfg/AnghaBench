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
struct nd_region {int /*<<< orphan*/  dev; } ;
struct nd_dax {int /*<<< orphan*/  nd_pfn; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nd_device_register (struct device*) ; 
 int /*<<< orphan*/  is_memory (int /*<<< orphan*/ *) ; 
 struct nd_dax* nd_dax_alloc (struct nd_region*) ; 
 struct device* nd_pfn_devinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct device *nd_dax_create(struct nd_region *nd_region)
{
	struct device *dev = NULL;
	struct nd_dax *nd_dax;

	if (!is_memory(&nd_region->dev))
		return NULL;

	nd_dax = nd_dax_alloc(nd_region);
	if (nd_dax)
		dev = nd_pfn_devinit(&nd_dax->nd_pfn, NULL);
	__nd_device_register(dev);
	return dev;
}