#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  iomode; } ;
struct pnfs_layout_segment {TYPE_1__ pls_range; } ;
struct pnfs_layout_range {int /*<<< orphan*/  iomode; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_return_segs; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  enum pnfs_iomode { ____Placeholder_pnfs_iomode } pnfs_iomode ;
struct TYPE_4__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  nfs_commit_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_mark_matching_lsegs_return (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,struct pnfs_layout_range*,int /*<<< orphan*/ ) ; 
 int pnfs_prepare_layoutreturn (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pnfs_send_layoutreturn (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pnfs_set_plh_return_info (struct pnfs_layout_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pnfs_error_mark_layout_for_return(struct inode *inode,
				       struct pnfs_layout_segment *lseg)
{
	struct pnfs_layout_hdr *lo = NFS_I(inode)->layout;
	struct pnfs_layout_range range = {
		.iomode = lseg->pls_range.iomode,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	};
	bool return_now = false;

	spin_lock(&inode->i_lock);
	if (!pnfs_layout_is_valid(lo)) {
		spin_unlock(&inode->i_lock);
		return;
	}
	pnfs_set_plh_return_info(lo, range.iomode, 0);
	/*
	 * mark all matching lsegs so that we are sure to have no live
	 * segments at hand when sending layoutreturn. See pnfs_put_lseg()
	 * for how it works.
	 */
	if (pnfs_mark_matching_lsegs_return(lo, &lo->plh_return_segs, &range, 0) != -EBUSY) {
		nfs4_stateid stateid;
		enum pnfs_iomode iomode;

		return_now = pnfs_prepare_layoutreturn(lo, &stateid, &iomode);
		spin_unlock(&inode->i_lock);
		if (return_now)
			pnfs_send_layoutreturn(lo, &stateid, iomode, false);
	} else {
		spin_unlock(&inode->i_lock);
		nfs_commit_inode(inode, 0);
	}
}