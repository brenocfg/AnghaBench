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
struct nd_region {int /*<<< orphan*/  pfn_ida; } ;
struct nd_pfn {struct nd_pfn* uuid; int /*<<< orphan*/  id; int /*<<< orphan*/  ndns; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nd_pfn*) ; 
 int /*<<< orphan*/  nd_detach_ndns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nd_pfn_release(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct nd_pfn *nd_pfn = to_nd_pfn(dev);

	dev_dbg(dev, "trace\n");
	nd_detach_ndns(&nd_pfn->dev, &nd_pfn->ndns);
	ida_simple_remove(&nd_region->pfn_ida, nd_pfn->id);
	kfree(nd_pfn->uuid);
	kfree(nd_pfn);
}