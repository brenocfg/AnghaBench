#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_27__ {scalar_t__ di_size; } ;
struct TYPE_31__ {TYPE_2__* d_ops; TYPE_1__ i_d; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_32__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_6__ xfs_dir2_leaf_tail_t ;
struct TYPE_29__ {void* magic; } ;
struct TYPE_30__ {TYPE_3__ info; } ;
struct TYPE_33__ {TYPE_4__ hdr; } ;
typedef  TYPE_7__ xfs_dir2_leaf_t ;
typedef  TYPE_7__ xfs_dir2_free_t ;
typedef  scalar_t__ xfs_dir2_db_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct TYPE_34__ {TYPE_15__* geo; int /*<<< orphan*/ * trans; TYPE_5__* dp; } ;
typedef  TYPE_9__ xfs_da_args_t ;
typedef  int uint ;
struct xfs_dir3_icfree_hdr {int nused; int nvalid; } ;
struct xfs_buf {int /*<<< orphan*/ * b_ops; TYPE_7__* b_addr; } ;
typedef  void* __be16 ;
struct TYPE_28__ {int /*<<< orphan*/  (* free_hdr_to_disk ) (TYPE_7__*,struct xfs_dir3_icfree_hdr*) ;void** (* free_bests_p ) (TYPE_7__*) ;int /*<<< orphan*/  (* free_hdr_from_disk ) (struct xfs_dir3_icfree_hdr*,TYPE_7__*) ;} ;
struct TYPE_26__ {int blksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  NULLDATAOFF ; 
 int /*<<< orphan*/  XFS_BLFT_DIR_LEAFN_BUF ; 
 int /*<<< orphan*/  XFS_DIR2_FREE_OFFSET ; 
 int /*<<< orphan*/  XFS_DIR2_FREE_SPACE ; 
 int /*<<< orphan*/  XFS_DIR2_LEAF1_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_LEAFN_MAGIC ; 
 int /*<<< orphan*/  be16_to_cpu (void*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icfree_hdr*,TYPE_7__*) ; 
 void** stub2 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*,struct xfs_dir3_icfree_hdr*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_to_node (TYPE_9__*) ; 
 scalar_t__ xfs_dir2_byte_to_db (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_bests (TYPE_9__*,struct xfs_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_header (TYPE_9__*,struct xfs_buf*) ; 
 int xfs_dir2_grow_inode (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 void** xfs_dir2_leaf_bests_p (TYPE_6__*) ; 
 TYPE_6__* xfs_dir2_leaf_tail_p (TYPE_15__*,TYPE_7__*) ; 
 int xfs_dir3_free_get_buf (TYPE_9__*,scalar_t__,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (TYPE_5__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_header (TYPE_9__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leafn_buf_ops ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ *,struct xfs_buf*,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_leaf_to_node(
	xfs_da_args_t		*args,		/* operation arguments */
	struct xfs_buf		*lbp)		/* leaf buffer */
{
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return value */
	struct xfs_buf		*fbp;		/* freespace buffer */
	xfs_dir2_db_t		fdb;		/* freespace block number */
	xfs_dir2_free_t		*free;		/* freespace structure */
	__be16			*from;		/* pointer to freespace entry */
	int			i;		/* leaf freespace index */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail structure */
	int			n;		/* count of live freespc ents */
	xfs_dir2_data_off_t	off;		/* freespace entry value */
	__be16			*to;		/* pointer to freespace entry */
	xfs_trans_t		*tp;		/* transaction pointer */
	struct xfs_dir3_icfree_hdr freehdr;

	trace_xfs_dir2_leaf_to_node(args);

	dp = args->dp;
	tp = args->trans;
	/*
	 * Add a freespace block to the directory.
	 */
	if ((error = xfs_dir2_grow_inode(args, XFS_DIR2_FREE_SPACE, &fdb))) {
		return error;
	}
	ASSERT(fdb == xfs_dir2_byte_to_db(args->geo, XFS_DIR2_FREE_OFFSET));
	/*
	 * Get the buffer for the new freespace block.
	 */
	error = xfs_dir3_free_get_buf(args, fdb, &fbp);
	if (error)
		return error;

	free = fbp->b_addr;
	dp->d_ops->free_hdr_from_disk(&freehdr, free);
	leaf = lbp->b_addr;
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	if (be32_to_cpu(ltp->bestcount) >
				(uint)dp->i_d.di_size / args->geo->blksize)
		return -EFSCORRUPTED;

	/*
	 * Copy freespace entries from the leaf block to the new block.
	 * Count active entries.
	 */
	from = xfs_dir2_leaf_bests_p(ltp);
	to = dp->d_ops->free_bests_p(free);
	for (i = n = 0; i < be32_to_cpu(ltp->bestcount); i++, from++, to++) {
		if ((off = be16_to_cpu(*from)) != NULLDATAOFF)
			n++;
		*to = cpu_to_be16(off);
	}

	/*
	 * Now initialize the freespace block header.
	 */
	freehdr.nused = n;
	freehdr.nvalid = be32_to_cpu(ltp->bestcount);

	dp->d_ops->free_hdr_to_disk(fbp->b_addr, &freehdr);
	xfs_dir2_free_log_bests(args, fbp, 0, freehdr.nvalid - 1);
	xfs_dir2_free_log_header(args, fbp);

	/*
	 * Converting the leaf to a leafnode is just a matter of changing the
	 * magic number and the ops. Do the change directly to the buffer as
	 * it's less work (and less code) than decoding the header to host
	 * format and back again.
	 */
	if (leaf->hdr.info.magic == cpu_to_be16(XFS_DIR2_LEAF1_MAGIC))
		leaf->hdr.info.magic = cpu_to_be16(XFS_DIR2_LEAFN_MAGIC);
	else
		leaf->hdr.info.magic = cpu_to_be16(XFS_DIR3_LEAFN_MAGIC);
	lbp->b_ops = &xfs_dir3_leafn_buf_ops;
	xfs_trans_buf_set_type(tp, lbp, XFS_BLFT_DIR_LEAFN_BUF);
	xfs_dir3_leaf_log_header(args, lbp);
	xfs_dir3_leaf_check(dp, lbp);
	return 0;
}