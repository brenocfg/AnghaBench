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
struct pnfs_layout_segment {int /*<<< orphan*/  pls_flags; int /*<<< orphan*/  pls_list; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_flags; int /*<<< orphan*/  plh_outstanding; int /*<<< orphan*/  plh_segs; int /*<<< orphan*/  plh_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LAYOUT_BULK_RECALL ; 
 int /*<<< orphan*/  NFS_LAYOUT_INVALID_STID ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN_REQUESTED ; 
 int /*<<< orphan*/  NFS_LSEG_LAYOUTRETURN ; 
 int /*<<< orphan*/  NFS_LSEG_VALID ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_layout_remove_lseg(struct pnfs_layout_hdr *lo,
		struct pnfs_layout_segment *lseg)
{
	WARN_ON(test_bit(NFS_LSEG_VALID, &lseg->pls_flags));
	list_del_init(&lseg->pls_list);
	/* Matched by pnfs_get_layout_hdr in pnfs_layout_insert_lseg */
	refcount_dec(&lo->plh_refcount);
	if (test_bit(NFS_LSEG_LAYOUTRETURN, &lseg->pls_flags))
		return;
	if (list_empty(&lo->plh_segs) &&
	    !test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags) &&
	    !test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags)) {
		if (atomic_read(&lo->plh_outstanding) == 0)
			set_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags);
		clear_bit(NFS_LAYOUT_BULK_RECALL, &lo->plh_flags);
	}
}