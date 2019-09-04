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
struct nd_region {scalar_t__ btt_seed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* dev_name (scalar_t__) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static ssize_t btt_seed_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_region *nd_region = to_nd_region(dev);
	ssize_t rc;

	nvdimm_bus_lock(dev);
	if (nd_region->btt_seed)
		rc = sprintf(buf, "%s\n", dev_name(nd_region->btt_seed));
	else
		rc = sprintf(buf, "\n");
	nvdimm_bus_unlock(dev);

	return rc;
}