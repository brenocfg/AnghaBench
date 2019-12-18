#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_range {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  iomode; } ;
struct TYPE_10__ {int /*<<< orphan*/  seqid; } ;
struct pnfs_layout_hdr {TYPE_4__ plh_stateid; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;
struct TYPE_11__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IOMODE_ANY ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_8__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  nfs4_stateid_is_newer (TYPE_4__*,TYPE_1__*) ; 
 scalar_t__ nfs4_stateid_match_other (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  nfs4_stateid_seqid_inc (TYPE_1__*) ; 
 int /*<<< orphan*/  pnfs_free_lseg_list (int /*<<< orphan*/ *) ; 
 scalar_t__ pnfs_layout_is_valid (struct pnfs_layout_hdr*) ; 
 int pnfs_mark_matching_lsegs_return (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,struct pnfs_layout_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool nfs4_layout_refresh_old_stateid(nfs4_stateid *dst,
		struct pnfs_layout_range *dst_range,
		struct inode *inode)
{
	struct pnfs_layout_hdr *lo;
	struct pnfs_layout_range range = {
		.iomode = IOMODE_ANY,
		.offset = 0,
		.length = NFS4_MAX_UINT64,
	};
	bool ret = false;
	LIST_HEAD(head);
	int err;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	if (lo &&  pnfs_layout_is_valid(lo) &&
	    nfs4_stateid_match_other(dst, &lo->plh_stateid)) {
		/* Is our call using the most recent seqid? If so, bump it */
		if (!nfs4_stateid_is_newer(&lo->plh_stateid, dst)) {
			nfs4_stateid_seqid_inc(dst);
			ret = true;
			goto out;
		}
		/* Try to update the seqid to the most recent */
		err = pnfs_mark_matching_lsegs_return(lo, &head, &range, 0);
		if (err != -EBUSY) {
			dst->seqid = lo->plh_stateid.seqid;
			*dst_range = range;
			ret = true;
		}
	}
out:
	spin_unlock(&inode->i_lock);
	pnfs_free_lseg_list(&head);
	return ret;
}