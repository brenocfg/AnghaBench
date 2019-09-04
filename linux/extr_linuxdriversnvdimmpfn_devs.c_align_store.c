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
struct nd_pfn {int /*<<< orphan*/  align; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t,char const*,char*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  nd_pfn_supported_alignments () ; 
 size_t nd_size_select_store (struct device*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 struct nd_pfn* to_nd_pfn_safe (struct device*) ; 

__attribute__((used)) static ssize_t align_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	ssize_t rc;

	device_lock(dev);
	nvdimm_bus_lock(dev);
	rc = nd_size_select_store(dev, buf, &nd_pfn->align,
			nd_pfn_supported_alignments());
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	device_unlock(dev);

	return rc ? rc : len;
}