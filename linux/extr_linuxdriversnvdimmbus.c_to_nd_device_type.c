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
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ND_DEVICE_DAX_PMEM ; 
 int ND_DEVICE_DIMM ; 
 int ND_DEVICE_REGION_BLK ; 
 int ND_DEVICE_REGION_PMEM ; 
 scalar_t__ is_memory (struct device*) ; 
 scalar_t__ is_nd_blk (struct device*) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_region (int /*<<< orphan*/ ) ; 
 scalar_t__ is_nvdimm (struct device*) ; 
 int nd_region_to_nstype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int to_nd_device_type(struct device *dev)
{
	if (is_nvdimm(dev))
		return ND_DEVICE_DIMM;
	else if (is_memory(dev))
		return ND_DEVICE_REGION_PMEM;
	else if (is_nd_blk(dev))
		return ND_DEVICE_REGION_BLK;
	else if (is_nd_dax(dev))
		return ND_DEVICE_DAX_PMEM;
	else if (is_nd_region(dev->parent))
		return nd_region_to_nstype(to_nd_region(dev->parent));

	return 0;
}