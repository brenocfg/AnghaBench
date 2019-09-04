#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_range {int dummy; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_stateid; struct inode* plh_inode; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeme ; 
 int /*<<< orphan*/  nfs4_stateid_match_other (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  pnfs_clear_layoutreturn_waitbit (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_free_lseg_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_free_returned_lsegs (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,struct pnfs_layout_range const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_mark_layout_stateid_invalid (struct pnfs_layout_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_mark_matching_lsegs_invalid (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,struct pnfs_layout_range const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_set_layout_stateid (struct pnfs_layout_hdr*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pnfs_layoutreturn_free_lsegs(struct pnfs_layout_hdr *lo,
		const nfs4_stateid *arg_stateid,
		const struct pnfs_layout_range *range,
		const nfs4_stateid *stateid)
{
	struct inode *inode = lo->plh_inode;
	LIST_HEAD(freeme);

	spin_lock(&inode->i_lock);
	if (!pnfs_layout_is_valid(lo) || !arg_stateid ||
	    !nfs4_stateid_match_other(&lo->plh_stateid, arg_stateid))
		goto out_unlock;
	if (stateid) {
		u32 seq = be32_to_cpu(arg_stateid->seqid);

		pnfs_mark_matching_lsegs_invalid(lo, &freeme, range, seq);
		pnfs_free_returned_lsegs(lo, &freeme, range, seq);
		pnfs_set_layout_stateid(lo, stateid, true);
	} else
		pnfs_mark_layout_stateid_invalid(lo, &freeme);
out_unlock:
	pnfs_clear_layoutreturn_waitbit(lo);
	spin_unlock(&inode->i_lock);
	pnfs_free_lseg_list(&freeme);

}