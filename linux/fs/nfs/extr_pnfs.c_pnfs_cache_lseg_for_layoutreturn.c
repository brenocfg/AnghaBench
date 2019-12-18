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
struct TYPE_2__ {int /*<<< orphan*/  iomode; } ;
struct pnfs_layout_segment {int /*<<< orphan*/  pls_list; TYPE_1__ pls_range; int /*<<< orphan*/  pls_flags; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_return_segs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LSEG_LAYOUTRETURN ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_set_plh_return_info (struct pnfs_layout_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
pnfs_cache_lseg_for_layoutreturn(struct pnfs_layout_hdr *lo,
		struct pnfs_layout_segment *lseg)
{
	if (test_and_clear_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags) &&
	    pnfs_layout_is_valid(lo)) {
		pnfs_set_plh_return_info(lo, lseg->pls_range.iomode, 0);
		list_move_tail(&lseg->pls_list, &lo->plh_return_segs);
		return true;
	}
	return false;
}