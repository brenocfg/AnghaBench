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
 int __nd_attach_ndns (struct device*,struct nd_namespace_common*,struct nd_namespace_common**) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (int /*<<< orphan*/ *) ; 

bool nd_attach_ndns(struct device *dev, struct nd_namespace_common *attach,
		struct nd_namespace_common **_ndns)
{
	bool claimed;

	nvdimm_bus_lock(&attach->dev);
	claimed = __nd_attach_ndns(dev, attach, _ndns);
	nvdimm_bus_unlock(&attach->dev);
	return claimed;
}