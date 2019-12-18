#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ iomode; scalar_t__ offset; int /*<<< orphan*/  length; } ;
struct pnfs_layout_segment {int /*<<< orphan*/  pls_flags; TYPE_1__ pls_range; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LSEG_LAYOUTRETURN ; 
 int /*<<< orphan*/  NFS_LSEG_ROC ; 
 scalar_t__ pnfs_calc_offset_end (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_calc_offset_length (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ff_lseg_merge(struct pnfs_layout_segment *new,
		struct pnfs_layout_segment *old)
{
	u64 new_end, old_end;

	if (test_bit(NFS_LSEG_LAYOUTRETURN, &old->pls_flags))
		return false;
	if (new->pls_range.iomode != old->pls_range.iomode)
		return false;
	old_end = pnfs_calc_offset_end(old->pls_range.offset,
			old->pls_range.length);
	if (old_end < new->pls_range.offset)
		return false;
	new_end = pnfs_calc_offset_end(new->pls_range.offset,
			new->pls_range.length);
	if (new_end < old->pls_range.offset)
		return false;

	/* Mergeable: copy info from 'old' to 'new' */
	if (new_end < old_end)
		new_end = old_end;
	if (new->pls_range.offset < old->pls_range.offset)
		new->pls_range.offset = old->pls_range.offset;
	new->pls_range.length = pnfs_calc_offset_length(new->pls_range.offset,
			new_end);
	if (test_bit(NFS_LSEG_ROC, &old->pls_flags))
		set_bit(NFS_LSEG_ROC, &new->pls_flags);
	return true;
}