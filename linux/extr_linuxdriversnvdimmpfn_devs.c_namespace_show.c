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
struct nd_pfn {TYPE_1__* ndns; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct nd_pfn* to_nd_pfn_safe (struct device*) ; 

__attribute__((used)) static ssize_t namespace_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	ssize_t rc;

	nvdimm_bus_lock(dev);
	rc = sprintf(buf, "%s\n", nd_pfn->ndns
			? dev_name(&nd_pfn->ndns->dev) : "");
	nvdimm_bus_unlock(dev);
	return rc;
}