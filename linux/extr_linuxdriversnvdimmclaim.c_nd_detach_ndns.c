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
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nd_detach_ndns (struct device*,struct nd_namespace_common**) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void nd_detach_ndns(struct device *dev,
		struct nd_namespace_common **_ndns)
{
	struct nd_namespace_common *ndns = *_ndns;

	if (!ndns)
		return;
	get_device(&ndns->dev);
	nvdimm_bus_lock(&ndns->dev);
	__nd_detach_ndns(dev, _ndns);
	nvdimm_bus_unlock(&ndns->dev);
	put_device(&ndns->dev);
}