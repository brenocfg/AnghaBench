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
struct nvdimm_bus {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nd_region_notify_driver_action (struct nvdimm_bus*,struct device*,int) ; 

void nd_region_disable(struct nvdimm_bus *nvdimm_bus, struct device *dev)
{
	nd_region_notify_driver_action(nvdimm_bus, dev, false);
}