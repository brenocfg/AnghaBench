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
struct nd_region {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int nvdimm_has_flush (struct nd_region*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static ssize_t deep_flush_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_region *nd_region = to_nd_region(dev);

	/*
	 * NOTE: in the nvdimm_has_flush() error case this attribute is
	 * not visible.
	 */
	return sprintf(buf, "%d\n", nvdimm_has_flush(nd_region));
}