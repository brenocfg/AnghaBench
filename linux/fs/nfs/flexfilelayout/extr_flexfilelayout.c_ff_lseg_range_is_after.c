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
typedef  scalar_t__ u64 ;
struct pnfs_layout_range {scalar_t__ iomode; scalar_t__ offset; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ IOMODE_READ ; 
 scalar_t__ pnfs_calc_offset_end (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ff_lseg_range_is_after(const struct pnfs_layout_range *l1,
		const struct pnfs_layout_range *l2)
{
	u64 end1, end2;

	if (l1->iomode != l2->iomode)
		return l1->iomode != IOMODE_READ;
	end1 = pnfs_calc_offset_end(l1->offset, l1->length);
	end2 = pnfs_calc_offset_end(l2->offset, l2->length);
	if (end1 < l2->offset)
		return false;
	if (end2 < l1->offset)
		return true;
	return l2->offset <= l1->offset;
}