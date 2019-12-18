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
struct pnfs_layout_range {scalar_t__ iomode; } ;

/* Variables and functions */
 scalar_t__ IOMODE_ANY ; 
 scalar_t__ pnfs_lseg_range_intersecting (struct pnfs_layout_range const*,struct pnfs_layout_range const*) ; 

__attribute__((used)) static bool
pnfs_should_free_range(const struct pnfs_layout_range *lseg_range,
		 const struct pnfs_layout_range *recall_range)
{
	return (recall_range->iomode == IOMODE_ANY ||
		lseg_range->iomode == recall_range->iomode) &&
	       pnfs_lseg_range_intersecting(lseg_range, recall_range);
}