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
struct nd_namespace_pmem {int /*<<< orphan*/  lbasize; } ;
struct nd_namespace_blk {int /*<<< orphan*/  lbasize; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  blk_lbasize_supported ; 
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 int /*<<< orphan*/  nd_size_select_show (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmem_lbasize_supported ; 
 struct nd_namespace_blk* to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 

__attribute__((used)) static ssize_t sector_size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	if (is_namespace_blk(dev)) {
		struct nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		return nd_size_select_show(nsblk->lbasize,
				blk_lbasize_supported, buf);
	}

	if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		return nd_size_select_show(nspm->lbasize,
				pmem_lbasize_supported, buf);
	}
	return -ENXIO;
}