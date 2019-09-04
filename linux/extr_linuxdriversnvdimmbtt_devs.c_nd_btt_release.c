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
struct nd_region {int /*<<< orphan*/  btt_ida; } ;
struct nd_btt {struct nd_btt* uuid; int /*<<< orphan*/  id; int /*<<< orphan*/  ndns; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nd_btt*) ; 
 int /*<<< orphan*/  nd_detach_ndns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nd_btt_release(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct nd_btt *nd_btt = to_nd_btt(dev);

	dev_dbg(dev, "trace\n");
	nd_detach_ndns(&nd_btt->dev, &nd_btt->ndns);
	ida_simple_remove(&nd_region->btt_ida, nd_btt->id);
	kfree(nd_btt->uuid);
	kfree(nd_btt);
}