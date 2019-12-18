#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_16__ {TYPE_1__* m_dirnameops; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_17__ {TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_18__ {int /*<<< orphan*/  address; int /*<<< orphan*/  hashval; } ;
typedef  TYPE_4__ xfs_dir2_leaf_entry_t ;
typedef  int xfs_dir2_dataptr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
struct TYPE_19__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ xfs_dir2_data_entry_t ;
struct TYPE_20__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_6__ xfs_dir2_block_tail_t ;
typedef  int xfs_dahash_t ;
struct TYPE_21__ {int hashval; int op_flags; int cmpresult; int /*<<< orphan*/  geo; int /*<<< orphan*/ * trans; TYPE_3__* dp; } ;
typedef  TYPE_7__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
typedef  enum xfs_dacmp { ____Placeholder_xfs_dacmp } xfs_dacmp ;
struct TYPE_15__ {int (* compname ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 scalar_t__ XFS_CMP_CASE ; 
 int XFS_CMP_DIFFERENT ; 
 int XFS_CMP_EXACT ; 
 int XFS_DA_OP_OKNOENT ; 
 int XFS_DIR2_NULL_DATAPTR ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* xfs_dir2_block_leaf_p (TYPE_6__*) ; 
 TYPE_6__* xfs_dir2_block_tail_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int) ; 
 int xfs_dir3_block_read (int /*<<< orphan*/ *,TYPE_3__*,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_data_check (TYPE_3__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 

__attribute__((used)) static int					/* error */
xfs_dir2_block_lookup_int(
	xfs_da_args_t		*args,		/* dir lookup arguments */
	struct xfs_buf		**bpp,		/* returned block buffer */
	int			*entno)		/* returned entry number */
{
	xfs_dir2_dataptr_t	addr;		/* data entry address */
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	struct xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	int			error;		/* error return value */
	xfs_dahash_t		hash;		/* found hash value */
	int			high;		/* binary search high index */
	int			low;		/* binary search low index */
	int			mid;		/* binary search current idx */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_trans_t		*tp;		/* transaction pointer */
	enum xfs_dacmp		cmp;		/* comparison result */

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;

	error = xfs_dir3_block_read(tp, dp, &bp);
	if (error)
		return error;

	hdr = bp->b_addr;
	xfs_dir3_data_check(dp, bp);
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Loop doing a binary search for our hash value.
	 * Find our entry, ENOENT if it's not there.
	 */
	for (low = 0, high = be32_to_cpu(btp->count) - 1; ; ) {
		ASSERT(low <= high);
		mid = (low + high) >> 1;
		if ((hash = be32_to_cpu(blp[mid].hashval)) == args->hashval)
			break;
		if (hash < args->hashval)
			low = mid + 1;
		else
			high = mid - 1;
		if (low > high) {
			ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
			xfs_trans_brelse(tp, bp);
			return -ENOENT;
		}
	}
	/*
	 * Back up to the first one with the right hash value.
	 */
	while (mid > 0 && be32_to_cpu(blp[mid - 1].hashval) == args->hashval) {
		mid--;
	}
	/*
	 * Now loop forward through all the entries with the
	 * right hash value looking for our name.
	 */
	do {
		if ((addr = be32_to_cpu(blp[mid].address)) == XFS_DIR2_NULL_DATAPTR)
			continue;
		/*
		 * Get pointer to the entry from the leaf.
		 */
		dep = (xfs_dir2_data_entry_t *)
			((char *)hdr + xfs_dir2_dataptr_to_off(args->geo, addr));
		/*
		 * Compare name and if it's an exact match, return the index
		 * and buffer. If it's the first case-insensitive match, store
		 * the index and buffer and continue looking for an exact match.
		 */
		cmp = mp->m_dirnameops->compname(args, dep->name, dep->namelen);
		if (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) {
			args->cmpresult = cmp;
			*bpp = bp;
			*entno = mid;
			if (cmp == XFS_CMP_EXACT)
				return 0;
		}
	} while (++mid < be32_to_cpu(btp->count) &&
			be32_to_cpu(blp[mid].hashval) == hash);

	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be doing a lookup (not a rename or replace).
	 * If a case-insensitive match was found earlier, return success.
	 */
	if (args->cmpresult == XFS_CMP_CASE)
		return 0;
	/*
	 * No match, release the buffer and return ENOENT.
	 */
	xfs_trans_brelse(tp, bp);
	return -ENOENT;
}