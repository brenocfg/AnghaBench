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
struct nd_blk_region {int dummy; } ;

/* Variables and functions */
 unsigned long ARCH_MEMREMAP_PMEM ; 

unsigned long nd_blk_memremap_flags(struct nd_blk_region *ndbr)
{
	/* pmem mapping properties are private to libnvdimm */
	return ARCH_MEMREMAP_PMEM;
}