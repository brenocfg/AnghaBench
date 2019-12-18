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
typedef  unsigned long __u64 ;

/* Variables and functions */
 scalar_t__ area_dst_alias ; 
 int /*<<< orphan*/  map_shared ; 

__attribute__((used)) static void hugetlb_alias_mapping(__u64 *start, size_t len, unsigned long offset)
{
	if (!map_shared)
		return;
	/*
	 * We can't zap just the pagetable with hugetlbfs because
	 * MADV_DONTEED won't work. So exercise -EEXIST on a alias
	 * mapping where the pagetables are not established initially,
	 * this way we'll exercise the -EEXEC at the fs level.
	 */
	*start = (unsigned long) area_dst_alias + offset;
}