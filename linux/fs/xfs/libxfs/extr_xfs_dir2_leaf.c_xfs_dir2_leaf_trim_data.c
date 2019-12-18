#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_16__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_17__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_3__ xfs_dir2_leaf_tail_t ;
struct xfs_dir2_data_hdr {scalar_t__ magic; } ;
typedef  struct xfs_dir2_data_hdr xfs_dir2_leaf_t ;
typedef  int xfs_dir2_db_t ;
struct TYPE_18__ {TYPE_11__* geo; int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct xfs_dir2_data_free {int /*<<< orphan*/  length; } ;
struct xfs_buf {struct xfs_dir2_data_hdr* b_addr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_15__ {scalar_t__ data_entry_offset; struct xfs_dir2_data_free* (* data_bestfree_p ) (struct xfs_dir2_data_hdr*) ;} ;
struct TYPE_14__ {scalar_t__ blksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct xfs_dir2_data_free* stub1 (struct xfs_dir2_data_hdr*) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_11__*,int) ; 
 int /*<<< orphan*/ * xfs_dir2_leaf_bests_p (TYPE_3__*) ; 
 TYPE_3__* xfs_dir2_leaf_tail_p (TYPE_11__*,struct xfs_dir2_data_hdr*) ; 
 int xfs_dir2_shrink_inode (TYPE_4__*,int,struct xfs_buf*) ; 
 int xfs_dir3_data_read (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_bests (TYPE_4__*,struct xfs_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_tail (TYPE_4__*,struct xfs_buf*) ; 
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