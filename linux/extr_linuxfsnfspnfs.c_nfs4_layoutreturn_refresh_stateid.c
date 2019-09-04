#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pnfs_layout_range {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  iomode; } ;
struct TYPE_7__ {int /*<<< orphan*/  seqid; } ;
struct pnfs_layout_hdr {TYPE_3__ plh_stateid; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; } ;
typedef  TYPE_1__ nfs4_stateid ;
struct TYPE_8__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IOMODE_ANY ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 TYPE_5__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  head ; 
 scalar_t__ nfs4_stateid_match_other (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  pnfs_free_lseg_list (int /*<<< orphan*/ *) ; 
 int pnfs_mark_matching_lsegs_return (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,struct pnfs_layout_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool nfs4_layoutreturn_refresh_stateid(nfs4_stateid *dst,
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
	if (lo && nfs4_stateid_match_other(dst, &lo->plh_stateid)) {
		err = pnfs_mark_matching_lsegs_return(lo, &head, &range, 0);
		if (err != -EBUSY) {
			dst->seqid = lo->plh_stateid.seqid;
			*dst_range = range;
			ret = true;
		}
	}
	spin_unlock(&inode->i_lock);
	pnfs_free_lseg_list(&head);
	return ret;
}