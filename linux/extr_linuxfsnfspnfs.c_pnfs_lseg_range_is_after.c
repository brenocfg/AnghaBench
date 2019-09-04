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
struct pnfs_layout_range {int dummy; } ;

/* Variables and functions */
 scalar_t__ pnfs_lseg_range_cmp (struct pnfs_layout_range const*,struct pnfs_layout_range const*) ; 

__attribute__((used)) static bool
pnfs_lseg_range_is_after(const struct pnfs_layout_range *l1,
		const struct pnfs_layout_range *l2)
{
	return pnfs_lseg_range_cmp(l1, l2) > 0;
}