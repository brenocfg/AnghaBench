#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_29__ {TYPE_1__* d_ops; } ;
typedef  TYPE_4__ xfs_inode_t ;
typedef  scalar_t__ xfs_fileoff_t ;
struct TYPE_30__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_5__ xfs_dir2_leaf_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
typedef  int /*<<< orphan*/  xfs_dir2_free_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct TYPE_28__ {int active; TYPE_2__* blk; } ;
struct TYPE_31__ {TYPE_3__ path; int /*<<< orphan*/ * mp; TYPE_7__* args; } ;
typedef  TYPE_6__ xfs_da_state_t ;
struct TYPE_32__ {TYPE_18__* geo; int /*<<< orphan*/ * trans; TYPE_4__* dp; } ;
typedef  TYPE_7__ xfs_da_args_t ;
struct xfs_dir3_icleaf_hdr {scalar_t__ magic; scalar_t__ stale; } ;
struct xfs_dir3_icfree_hdr {int nvalid; int /*<<< orphan*/  firstdb; } ;
struct xfs_buf {int /*<<< orphan*/ * b_ops; int /*<<< orphan*/ * b_addr; } ;
struct TYPE_27__ {struct xfs_buf* bp; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* leaf_hdr_to_disk ) (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ;int /*<<< orphan*/  (* free_bests_p ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* free_hdr_from_disk ) (struct xfs_dir3_icfree_hdr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_25__ {scalar_t__ fsbcount; scalar_t__ freeblk; scalar_t__ blksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_BLFT_DIR_LEAF1_BUF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_DIR2_FREE_OFFSET ; 
 scalar_t__ XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAF_OFFSET ; 
 scalar_t__ XFS_DIR3_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR3_LEAFN_MAGIC ; 
 scalar_t__ XFS_FSB_TO_B (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct xfs_dir3_icfree_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_node_to_leaf (TYPE_7__*) ; 
 int xfs_bmap_last_before (int /*<<< orphan*/ *,TYPE_4__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int xfs_bmap_last_offset (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_byte_to_db (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int xfs_dir2_free_read (int /*<<< orphan*/ *,TYPE_4__*,scalar_t__,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_bests_p (TYPE_5__*) ; 
 TYPE_5__* xfs_dir2_leaf_tail_p (TYPE_18__*,int /*<<< orphan*/ *) ; 
 int xfs_dir2_leaf_to_block (TYPE_7__*,struct xfs_buf*,int /*<<< orphan*/ *) ; 
 int xfs_dir2_node_trim_free (TYPE_7__*,scalar_t__,int*) ; 
 int xfs_dir2_shrink_inode (TYPE_7__*,int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf1_buf_ops ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (TYPE_4__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_compact (TYPE_7__*,struct xfs_dir3_icleaf_hdr*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_bests (TYPE_7__*,struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_header (TYPE_7__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_tail (TYPE_7__*,struct xfs_buf*) ; 
 scalar_t__ xfs_dir3_leaf_size (struct xfs_dir3_icleaf_hdr*,int) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ *,struct xfs_buf*,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_node_to_leaf(
	xfs_da_state_t		*state)		/* directory operation state */
{
	xfs_da_args_t		*args;		/* operation arguments */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	struct xfs_buf		*fbp;		/* buffer for freespace block */
	xfs_fileoff_t		fo;		/* freespace file offset */
	xfs_dir2_free_t		*free;		/* freespace structure */
	struct xfs_buf		*lbp;		/* buffer for leaf block */
	xfs_dir2_leaf_tail_t	*ltp;		/* tail of leaf structure */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			rval;		/* successful free trim? */
	xfs_trans_t		*tp;		/* transaction pointer */
	struct xfs_dir3_icleaf_hdr leafhdr;
	struct xfs_dir3_icfree_hdr freehdr;

	/*
	 * There's more than a leaf level in the btree, so there must
	 * be multiple leafn blocks.  Give up.
	 */
	if (state->path.active > 1)
		return 0;
	args = state->args;

	trace_xfs_dir2_node_to_leaf(args);

	mp = state->mp;
	dp = args->dp;
	tp = args->trans;
	/*
	 * Get the last offset in the file.
	 */
	if ((error = xfs_bmap_last_offset(dp, &fo, XFS_DATA_FORK))) {
		return error;
	}
	fo -= args->geo->fsbcount;
	/*
	 * If there are freespace blocks other than the first one,
	 * take this opportunity to remove trailing empty freespace blocks
	 * that may have been left behind during no-space-reservation
	 * operations.
	 */
	while (fo > args->geo->freeblk) {
		if ((error = xfs_dir2_node_trim_free(args, fo, &rval))) {
			return error;
		}
		if (rval)
			fo -= args->geo->fsbcount;
		else
			return 0;
	}
	/*
	 * Now find the block just before the freespace block.
	 */
	if ((error = xfs_bmap_last_before(tp, dp, &fo, XFS_DATA_FORK))) {
		return error;
	}
	/*
	 * If it's not the single leaf block, give up.
	 */
	if (XFS_FSB_TO_B(mp, fo) > XFS_DIR2_LEAF_OFFSET + args->geo->blksize)
		return 0;
	lbp = state->path.blk[0].bp;
	leaf = lbp->b_addr;
	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);

	ASSERT(leafhdr.magic == XFS_DIR2_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_DIR3_LEAFN_MAGIC);

	/*
	 * Read the freespace block.
	 */
	error = xfs_dir2_free_read(tp, dp,  args->geo->freeblk, &fbp);
	if (error)
		return error;
	free = fbp->b_addr;
	dp->d_ops->free_hdr_from_disk(&freehdr, free);

	ASSERT(!freehdr.firstdb);

	/*
	 * Now see if the leafn and free data will fit in a leaf1.
	 * If not, release the buffer and give up.
	 */
	if (xfs_dir3_leaf_size(&leafhdr, freehdr.nvalid) > args->geo->blksize) {
		xfs_trans_brelse(tp, fbp);
		return 0;
	}

	/*
	 * If the leaf has any stale entries in it, compress them out.
	 */
	if (leafhdr.stale)
		xfs_dir3_leaf_compact(args, &leafhdr, lbp);

	lbp->b_ops = &xfs_dir3_leaf1_buf_ops;
	xfs_trans_buf_set_type(tp, lbp, XFS_BLFT_DIR_LEAF1_BUF);
	leafhdr.magic = (leafhdr.magic == XFS_DIR2_LEAFN_MAGIC)
					? XFS_DIR2_LEAF1_MAGIC
					: XFS_DIR3_LEAF1_MAGIC;

	/*
	 * Set up the leaf tail from the freespace block.
	 */
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	ltp->bestcount = cpu_to_be32(freehdr.nvalid);

	/*
	 * Set up the leaf bests table.
	 */
	memcpy(xfs_dir2_leaf_bests_p(ltp), dp->d_ops->free_bests_p(free),
		freehdr.nvalid * sizeof(xfs_dir2_data_off_t));

	dp->d_ops->leaf_hdr_to_disk(leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, lbp);
	xfs_dir3_leaf_log_bests(args, lbp, 0, be32_to_cpu(ltp->bestcount) - 1);
	xfs_dir3_leaf_log_tail(args, lbp);
	xfs_dir3_leaf_check(dp, lbp);

	/*
	 * Get rid of the freespace block.
	 */
	error = xfs_dir2_shrink_inode(args,
			xfs_dir2_byte_to_db(args->geo, XFS_DIR2_FREE_OFFSET),
			fbp);
	if (error) {
		/*
		 * This can't fail here because it can only happen when
		 * punching out the middle of an extent, and this is an
		 * isolated block.
		 */
		ASSERT(error != -ENOSPC);
		return error;
	}
	fbp = NULL;
	/*
	 * Now see if we can convert the single-leaf directory
	 * down to a block form directory.
	 * This routine always kills the dabuf for the leaf, so
	 * eliminate it from the path.
	 */
	error = xfs_dir2_leaf_to_block(args, lbp, NULL);
	state->path.blk[0].bp = NULL;
	return error;
}