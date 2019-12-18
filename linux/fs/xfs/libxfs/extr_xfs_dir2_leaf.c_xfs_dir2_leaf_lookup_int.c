#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_19__ {TYPE_2__* m_dirnameops; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_20__ {TYPE_1__* d_ops; TYPE_3__* i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  address; int /*<<< orphan*/  hashval; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
typedef  int xfs_dir2_db_t ;
struct TYPE_21__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ xfs_dir2_data_entry_t ;
struct TYPE_22__ {scalar_t__ hashval; int cmpresult; int op_flags; TYPE_12__* geo; int /*<<< orphan*/ * trans; TYPE_4__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;
struct xfs_dir3_icleaf_hdr {int count; } ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
typedef  enum xfs_dacmp { ____Placeholder_xfs_dacmp } xfs_dacmp ;
struct TYPE_18__ {int (* compname ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  leafblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 scalar_t__ XFS_CMP_CASE ; 
 int XFS_CMP_DIFFERENT ; 
 int XFS_CMP_EXACT ; 
 int XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DIR2_NULL_DATAPTR ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct xfs_dir2_leaf_entry* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_dir2_dataptr_to_db (TYPE_12__*,scalar_t__) ; 
 int xfs_dir2_dataptr_to_off (TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_12__*,int) ; 
 int xfs_dir2_leaf_search_hash (TYPE_6__*,struct xfs_buf*) ; 
 int xfs_dir3_data_read (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (TYPE_4__*,struct xfs_buf*) ; 
 int xfs_dir3_leaf_read (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 

__attribute__((used)) static int					/* error */
xfs_dir2_leaf_lookup_int(
	xfs_da_args_t		*args,		/* operation arguments */
	struct xfs_buf		**lbpp,		/* out: leaf buffer */
	int			*indexp,	/* out: index in leaf block */
	struct xfs_buf		**dbpp)		/* out: data buffer */
{
	xfs_dir2_db_t		curdb = -1;	/* current data block number */
	struct xfs_buf		*dbp = NULL;	/* data buffer */
	xfs_dir2_data_entry_t	*dep;		/* data entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	int			index;		/* index in leaf block */
	struct xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_dir2_db_t		newdb;		/* new data block number */
	xfs_trans_t		*tp;		/* transaction pointer */
	xfs_dir2_db_t		cidb = -1;	/* case match data block no. */
	enum xfs_dacmp		cmp;		/* name compare result */
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_dir3_icleaf_hdr leafhdr;

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;

	error = xfs_dir3_leaf_read(tp, dp, args->geo->leafblk, -1, &lbp);
	if (error)
		return error;

	*lbpp = lbp;
	leaf = lbp->b_addr;
	xfs_dir3_leaf_check(dp, lbp);
	ents = dp->d_ops->leaf_ents_p(leaf);
	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);

	/*
	 * Look for the first leaf entry with our hash value.
	 */
	index = xfs_dir2_leaf_search_hash(args, lbp);
	/*
	 * Loop over all the entries with the right hash value
	 * looking to match the name.
	 */
	for (lep = &ents[index];
	     index < leafhdr.count && be32_to_cpu(lep->hashval) == args->hashval;
	     lep++, index++) {
		/*
		 * Skip over stale leaf entries.
		 */
		if (be32_to_cpu(lep->address) == XFS_DIR2_NULL_DATAPTR)
			continue;
		/*
		 * Get the new data block number.
		 */
		newdb = xfs_dir2_dataptr_to_db(args->geo,
					       be32_to_cpu(lep->address));
		/*
		 * If it's not the same as the old data block number,
		 * need to pitch the old one and read the new one.
		 */
		if (newdb != curdb) {
			if (dbp)
				xfs_trans_brelse(tp, dbp);
			error = xfs_dir3_data_read(tp, dp,
					   xfs_dir2_db_to_da(args->geo, newdb),
					   -1, &dbp);
			if (error) {
				xfs_trans_brelse(tp, lbp);
				return error;
			}
			curdb = newdb;
		}
		/*
		 * Point to the data entry.
		 */
		dep = (xfs_dir2_data_entry_t *)((char *)dbp->b_addr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(lep->address)));
		/*
		 * Compare name and if it's an exact match, return the index
		 * and buffer. If it's the first case-insensitive match, store
		 * the index and buffer and continue looking for an exact match.
		 */
		cmp = mp->m_dirnameops->compname(args, dep->name, dep->namelen);
		if (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) {
			args->cmpresult = cmp;
			*indexp = index;
			/* case exact match: return the current buffer. */
			if (cmp == XFS_CMP_EXACT) {
				*dbpp = dbp;
				return 0;
			}
			cidb = curdb;
		}
	}
	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be doing a lookup (not a rename or remove).
	 * If a case-insensitive match was found earlier, re-read the
	 * appropriate data block if required and return it.
	 */
	if (args->cmpresult == XFS_CMP_CASE) {
		ASSERT(cidb != -1);
		if (cidb != curdb) {
			xfs_trans_brelse(tp, dbp);
			error = xfs_dir3_data_read(tp, dp,
					   xfs_dir2_db_to_da(args->geo, cidb),
					   -1, &dbp);
			if (error) {
				xfs_trans_brelse(tp, lbp);
				return error;
			}
		}
		*dbpp = dbp;
		return 0;
	}
	/*
	 * No match found, return -ENOENT.
	 */
	ASSERT(cidb == -1);
	if (dbp)
		xfs_trans_brelse(tp, dbp);
	xfs_trans_brelse(tp, lbp);
	return -ENOENT;
}