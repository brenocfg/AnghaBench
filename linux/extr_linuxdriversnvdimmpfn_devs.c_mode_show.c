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
struct nd_pfn {int mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  PFN_MODE_PMEM 129 
#define  PFN_MODE_RAM 128 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct nd_pfn* to_nd_pfn_safe (struct device*) ; 

__attribute__((used)) static ssize_t mode_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

	switch (nd_pfn->mode) {
	case PFN_MODE_RAM:
		return sprintf(buf, "ram\n");
	case PFN_MODE_PMEM:
		return sprintf(buf, "pmem\n");
	default:
		return sprintf(buf, "none\n");
	}
}