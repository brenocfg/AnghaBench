#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_inode_t ;
struct TYPE_9__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_1__ xfs_dir2_leaf_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
typedef  int /*<<< orphan*/  xfs_dir2_db_t ;
struct TYPE_10__ {int /*<<< orphan*/  geo; int /*<<< orphan*/ * trans; int /*<<< orphan*/ * dp; } ;
typedef  TYPE_2__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_dir2_leaf_bests_p (TYPE_1__*) ; 
 TYPE_1__* xfs_dir2_leaf_tail_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_dir2_shrink_inode (TYPE_2__*,int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int xfs_dir3_data_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_bests (TYPE_2__*,struct xfs_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_tail (TYPE_2__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_leaf_trim_data(
	xfs_da_args_t		*args,		/* operation arguments */
	struct xfs_buf		*lbp,		/* leaf buffer */
	xfs_dir2_db_t		db)		/* data block number */
{
	__be16			*bestsp;	/* leaf bests table */
	struct xfs_buf		*dbp;		/* data block buffer */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return value */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail structure */
	xfs_trans_t		*tp;		/* transaction pointer */

	dp = args->dp;
	tp = args->trans;
	/*
	 * Read the offending data block.  We need its buffer.
	 */
	error = xfs_dir3_data_read(tp, dp, xfs_dir2_db_to_da(args->geo, db),
				   -1, &dbp);
	if (error)
		return error;

	leaf = lbp->b_addr;
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);

#ifdef DEBUG
{
	struct xfs_dir2_data_hdr *hdr = dbp->b_addr;
	struct xfs_dir2_data_free *bf = dp->d_ops->data_bestfree_p(hdr);

	ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC));
	ASSERT(be16_to_cpu(bf[0].length) ==
	       args->geo->blksize - dp->d_ops->data_entry_offset);
	ASSERT(db == be32_to_cpu(ltp->bestcount) - 1);
}
#endif

	/*
	 * Get rid of the data block.
	 */
	if ((error = xfs_dir2_shrink_inode(args, db, dbp))) {
		ASSERT(error != -ENOSPC);
		xfs_trans_brelse(tp, dbp);
		return error;
	}
	/*
	 * Eliminate the last bests entry from the table.
	 */
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	be32_add_cpu(&ltp->bestcount, -1);
	memmove(&bestsp[1], &bestsp[0], be32_to_cpu(ltp->bestcount) * sizeof(*bestsp));
	xfs_dir3_leaf_log_tail(args, lbp);
	xfs_dir3_leaf_log_bests(args, lbp, 0, be32_to_cpu(ltp->bestcount) - 1);
	return 0;
}