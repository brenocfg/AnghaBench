#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_28__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  address; } ;
typedef  struct xfs_dir2_leaf_entry xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_free_t ;
typedef  scalar_t__ xfs_dir2_db_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
struct TYPE_29__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_3__ xfs_dir2_data_entry_t ;
struct TYPE_30__ {scalar_t__ blkno; int index; struct xfs_buf* bp; } ;
typedef  TYPE_4__ xfs_da_state_blk_t ;
struct TYPE_31__ {scalar_t__ total; TYPE_15__* geo; int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
typedef  int uint ;
struct xfs_dir3_icleaf_hdr {int stale; int count; } ;
struct xfs_dir3_icfree_hdr {scalar_t__ firstdb; } ;
struct xfs_dir2_data_free {int /*<<< orphan*/  length; } ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
typedef  int /*<<< orphan*/  ents ;
struct TYPE_27__ {scalar_t__ (* db_to_fdb ) (TYPE_15__*,scalar_t__) ;scalar_t__ (* free_max_bests ) (TYPE_15__*) ;int (* db_to_fdindex ) (TYPE_15__*,scalar_t__) ;int data_entry_offset; scalar_t__ leaf_hdr_size; int /*<<< orphan*/  (* free_hdr_from_disk ) (struct xfs_dir3_icfree_hdr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* data_entsize ) (int /*<<< orphan*/ ) ;struct xfs_dir2_data_free* (* data_bestfree_p ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* leaf_hdr_to_disk ) (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_26__ {int blksize; scalar_t__ magicpct; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  XFS_DIR2_FREE_OFFSET ; 
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 struct xfs_dir2_leaf_entry* stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ; 
 struct xfs_dir2_data_free* stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (TYPE_15__*,scalar_t__) ; 
 int /*<<< orphan*/  stub7 (struct xfs_dir3_icfree_hdr*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub8 (TYPE_15__*) ; 
 int stub9 (TYPE_15__*,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leafn_remove (TYPE_5__*,int) ; 
 scalar_t__ xfs_dir2_byte_to_db (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (TYPE_5__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (TYPE_5__*,struct xfs_buf*,int,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ xfs_dir2_dataptr_to_db (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int xfs_dir2_dataptr_to_off (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_15__*,scalar_t__) ; 
 int xfs_dir2_free_read (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 int xfs_dir2_shrink_inode (TYPE_5__*,scalar_t__,struct xfs_buf*) ; 
 int xfs_dir3_data_block_free (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,struct xfs_buf*,int) ; 
 int /*<<< orphan*/  xfs_dir3_data_check (TYPE_2__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (TYPE_2__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_ents (TYPE_5__*,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_header (TYPE_5__*,struct xfs_buf*) ; 

__attribute__((used)) static int					/* error */
xfs_dir2_leafn_remove(
	xfs_da_args_t		*args,		/* operation arguments */
	struct xfs_buf		*bp,		/* leaf buffer */
	int			index,		/* leaf entry index */
	xfs_da_state_blk_t	*dblk,		/* data block */
	int			*rval)		/* resulting block needs join */
{
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_db_t		db;		/* data block number */
	struct xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	int			longest;	/* longest data free entry */
	int			off;		/* data block entry offset */
	int			needlog;	/* need to log data header */
	int			needscan;	/* need to rescan data frees */
	xfs_trans_t		*tp;		/* transaction pointer */
	struct xfs_dir2_data_free *bf;		/* bestfree table */
	struct xfs_dir3_icleaf_hdr leafhdr;
	struct xfs_dir2_leaf_entry *ents;

	trace_xfs_dir2_leafn_remove(args, index);

	dp = args->dp;
	tp = args->trans;
	leaf = bp->b_addr;
	dp->d_ops->leaf_hdr_from_disk(&leafhdr, leaf);
	ents = dp->d_ops->leaf_ents_p(leaf);

	/*
	 * Point to the entry we're removing.
	 */
	lep = &ents[index];

	/*
	 * Extract the data block and offset from the entry.
	 */
	db = xfs_dir2_dataptr_to_db(args->geo, be32_to_cpu(lep->address));
	ASSERT(dblk->blkno == db);
	off = xfs_dir2_dataptr_to_off(args->geo, be32_to_cpu(lep->address));
	ASSERT(dblk->index == off);

	/*
	 * Kill the leaf entry by marking it stale.
	 * Log the leaf block changes.
	 */
	leafhdr.stale++;
	dp->d_ops->leaf_hdr_to_disk(leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, bp);

	lep->address = cpu_to_be32(XFS_DIR2_NULL_DATAPTR);
	xfs_dir3_leaf_log_ents(args, bp, index, index);

	/*
	 * Make the data entry free.  Keep track of the longest freespace
	 * in the data block in case it changes.
	 */
	dbp = dblk->bp;
	hdr = dbp->b_addr;
	dep = (xfs_dir2_data_entry_t *)((char *)hdr + off);
	bf = dp->d_ops->data_bestfree_p(hdr);
	longest = be16_to_cpu(bf[0].length);
	needlog = needscan = 0;
	xfs_dir2_data_make_free(args, dbp, off,
		dp->d_ops->data_entsize(dep->namelen), &needlog, &needscan);
	/*
	 * Rescan the data block freespaces for bestfree.
	 * Log the data block header if needed.
	 */
	if (needscan)
		xfs_dir2_data_freescan(dp, hdr, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(args, dbp);
	xfs_dir3_data_check(dp, dbp);
	/*
	 * If the longest data block freespace changes, need to update
	 * the corresponding freeblock entry.
	 */
	if (longest < be16_to_cpu(bf[0].length)) {
		int		error;		/* error return value */
		struct xfs_buf	*fbp;		/* freeblock buffer */
		xfs_dir2_db_t	fdb;		/* freeblock block number */
		int		findex;		/* index in freeblock entries */
		xfs_dir2_free_t	*free;		/* freeblock structure */

		/*
		 * Convert the data block number to a free block,
		 * read in the free block.
		 */
		fdb = dp->d_ops->db_to_fdb(args->geo, db);
		error = xfs_dir2_free_read(tp, dp,
					   xfs_dir2_db_to_da(args->geo, fdb),
					   &fbp);
		if (error)
			return error;
		free = fbp->b_addr;
#ifdef DEBUG
	{
		struct xfs_dir3_icfree_hdr freehdr;
		dp->d_ops->free_hdr_from_disk(&freehdr, free);
		ASSERT(freehdr.firstdb == dp->d_ops->free_max_bests(args->geo) *
			(fdb - xfs_dir2_byte_to_db(args->geo,
						   XFS_DIR2_FREE_OFFSET)));
	}
#endif
		/*
		 * Calculate which entry we need to fix.
		 */
		findex = dp->d_ops->db_to_fdindex(args->geo, db);
		longest = be16_to_cpu(bf[0].length);
		/*
		 * If the data block is now empty we can get rid of it
		 * (usually).
		 */
		if (longest == args->geo->blksize -
			       dp->d_ops->data_entry_offset) {
			/*
			 * Try to punch out the data block.
			 */
			error = xfs_dir2_shrink_inode(args, db, dbp);
			if (error == 0) {
				dblk->bp = NULL;
				hdr = NULL;
			}
			/*
			 * We can get ENOSPC if there's no space reservation.
			 * In this case just drop the buffer and some one else
			 * will eventually get rid of the empty block.
			 */
			else if (!(error == -ENOSPC && args->total == 0))
				return error;
		}
		/*
		 * If we got rid of the data block, we can eliminate that entry
		 * in the free block.
		 */
		error = xfs_dir3_data_block_free(args, hdr, free,
						 fdb, findex, fbp, longest);
		if (error)
			return error;
	}

	xfs_dir3_leaf_check(dp, bp);
	/*
	 * Return indication of whether this leaf block is empty enough
	 * to justify trying to join it with a neighbor.
	 */
	*rval = (dp->d_ops->leaf_hdr_size +
		 (uint)sizeof(ents[0]) * (leafhdr.count - leafhdr.stale)) <
		args->geo->magicpct;
	return 0;
}