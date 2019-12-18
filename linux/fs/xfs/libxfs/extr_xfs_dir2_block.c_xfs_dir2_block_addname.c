#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_36__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_37__ {scalar_t__ address; scalar_t__ hashval; } ;
typedef  TYPE_3__ xfs_dir2_leaf_entry_t ;
struct TYPE_38__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_4__ xfs_dir2_data_unused_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
struct TYPE_39__ {int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  inumber; } ;
typedef  TYPE_5__ xfs_dir2_data_entry_t ;
typedef  scalar_t__ xfs_dir2_data_aoff_t ;
struct TYPE_40__ {scalar_t__ stale; scalar_t__ count; } ;
typedef  TYPE_6__ xfs_dir2_block_tail_t ;
typedef  int xfs_dahash_t ;
struct TYPE_41__ {int op_flags; scalar_t__ total; int hashval; int /*<<< orphan*/  filetype; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; int /*<<< orphan*/  geo; int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_7__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_35__ {int (* data_entsize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* data_entry_tag_p ) (TYPE_5__*) ;int /*<<< orphan*/  (* data_put_ftype ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int XFS_DA_OP_JUSTCHECK ; 
 int XFS_DIR2_NULL_DATAPTR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_add_cpu (scalar_t__*,int) ; 
 int be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 
 int min (int,int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub3 (TYPE_5__*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_addname (TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_compact (TYPE_7__*,struct xfs_buf*,int /*<<< orphan*/ *,TYPE_6__*,TYPE_3__*,int*,int*,int*) ; 
 TYPE_3__* xfs_dir2_block_leaf_p (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_leaf (int /*<<< orphan*/ *,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_tail (int /*<<< orphan*/ *,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir2_block_need_space (TYPE_2__*,int /*<<< orphan*/ *,TYPE_6__*,TYPE_3__*,int /*<<< orphan*/ **,TYPE_4__**,TYPE_4__**,int*,int) ; 
 TYPE_6__* xfs_dir2_block_tail_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_dir2_block_to_leaf (TYPE_7__*,struct xfs_buf*) ; 
 int xfs_dir2_byte_to_dataptr (int) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (TYPE_7__*,struct xfs_buf*,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (TYPE_7__*,struct xfs_buf*) ; 
 int xfs_dir2_data_use_free (TYPE_7__*,struct xfs_buf*,TYPE_4__*,scalar_t__,scalar_t__,int*,int*) ; 
 int xfs_dir2_leaf_addname (TYPE_7__*) ; 
 int xfs_dir3_block_read (int /*<<< orphan*/ *,TYPE_2__*,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dir3_data_check (TYPE_2__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_block_addname(
	xfs_da_args_t		*args)		/* directory op arguments */
{
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	struct xfs_buf		*bp;		/* buffer for block */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	int			compact;	/* need to compact leaf ents */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* directory inode */
	xfs_dir2_data_unused_t	*dup;		/* block unused entry */
	int			error;		/* error return value */
	xfs_dir2_data_unused_t	*enddup=NULL;	/* unused at end of data */
	xfs_dahash_t		hash;		/* hash value of found entry */
	int			high;		/* high index for binary srch */
	int			highstale;	/* high stale index */
	int			lfloghigh=0;	/* last final leaf to log */
	int			lfloglow=0;	/* first final leaf to log */
	int			len;		/* length of the new entry */
	int			low;		/* low index for binary srch */
	int			lowstale;	/* low stale index */
	int			mid=0;		/* midpoint for binary srch */
	int			needlog;	/* need to log header */
	int			needscan;	/* need to rescan freespace */
	__be16			*tagp;		/* pointer to tag value */
	xfs_trans_t		*tp;		/* transaction structure */

	trace_xfs_dir2_block_addname(args);

	dp = args->dp;
	tp = args->trans;

	/* Read the (one and only) directory block into bp. */
	error = xfs_dir3_block_read(tp, dp, &bp);
	if (error)
		return error;

	len = dp->d_ops->data_entsize(args->namelen);

	/*
	 * Set up pointers to parts of the block.
	 */
	hdr = bp->b_addr;
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);

	/*
	 * Find out if we can reuse stale entries or whether we need extra
	 * space for entry and new leaf.
	 */
	xfs_dir2_block_need_space(dp, hdr, btp, blp, &tagp, &dup,
				  &enddup, &compact, len);

	/*
	 * Done everything we need for a space check now.
	 */
	if (args->op_flags & XFS_DA_OP_JUSTCHECK) {
		xfs_trans_brelse(tp, bp);
		if (!dup)
			return -ENOSPC;
		return 0;
	}

	/*
	 * If we don't have space for the new entry & leaf ...
	 */
	if (!dup) {
		/* Don't have a space reservation: return no-space.  */
		if (args->total == 0)
			return -ENOSPC;
		/*
		 * Convert to the next larger format.
		 * Then add the new entry in that format.
		 */
		error = xfs_dir2_block_to_leaf(args, bp);
		if (error)
			return error;
		return xfs_dir2_leaf_addname(args);
	}

	needlog = needscan = 0;

	/*
	 * If need to compact the leaf entries, do it now.
	 */
	if (compact) {
		xfs_dir2_block_compact(args, bp, hdr, btp, blp, &needlog,
				      &lfloghigh, &lfloglow);
		/* recalculate blp post-compaction */
		blp = xfs_dir2_block_leaf_p(btp);
	} else if (btp->stale) {
		/*
		 * Set leaf logging boundaries to impossible state.
		 * For the no-stale case they're set explicitly.
		 */
		lfloglow = be32_to_cpu(btp->count);
		lfloghigh = -1;
	}

	/*
	 * Find the slot that's first lower than our hash value, -1 if none.
	 */
	for (low = 0, high = be32_to_cpu(btp->count) - 1; low <= high; ) {
		mid = (low + high) >> 1;
		if ((hash = be32_to_cpu(blp[mid].hashval)) == args->hashval)
			break;
		if (hash < args->hashval)
			low = mid + 1;
		else
			high = mid - 1;
	}
	while (mid >= 0 && be32_to_cpu(blp[mid].hashval) >= args->hashval) {
		mid--;
	}
	/*
	 * No stale entries, will use enddup space to hold new leaf.
	 */
	if (!btp->stale) {
		xfs_dir2_data_aoff_t	aoff;

		/*
		 * Mark the space needed for the new leaf entry, now in use.
		 */
		aoff = (xfs_dir2_data_aoff_t)((char *)enddup - (char *)hdr +
				be16_to_cpu(enddup->length) - sizeof(*blp));
		error = xfs_dir2_data_use_free(args, bp, enddup, aoff,
				(xfs_dir2_data_aoff_t)sizeof(*blp), &needlog,
				&needscan);
		if (error)
			return error;

		/*
		 * Update the tail (entry count).
		 */
		be32_add_cpu(&btp->count, 1);
		/*
		 * If we now need to rebuild the bestfree map, do so.
		 * This needs to happen before the next call to use_free.
		 */
		if (needscan) {
			xfs_dir2_data_freescan(dp, hdr, &needlog);
			needscan = 0;
		}
		/*
		 * Adjust pointer to the first leaf entry, we're about to move
		 * the table up one to open up space for the new leaf entry.
		 * Then adjust our index to match.
		 */
		blp--;
		mid++;
		if (mid)
			memmove(blp, &blp[1], mid * sizeof(*blp));
		lfloglow = 0;
		lfloghigh = mid;
	}
	/*
	 * Use a stale leaf for our new entry.
	 */
	else {
		for (lowstale = mid;
		     lowstale >= 0 &&
			blp[lowstale].address !=
			cpu_to_be32(XFS_DIR2_NULL_DATAPTR);
		     lowstale--)
			continue;
		for (highstale = mid + 1;
		     highstale < be32_to_cpu(btp->count) &&
			blp[highstale].address !=
			cpu_to_be32(XFS_DIR2_NULL_DATAPTR) &&
			(lowstale < 0 || mid - lowstale > highstale - mid);
		     highstale++)
			continue;
		/*
		 * Move entries toward the low-numbered stale entry.
		 */
		if (lowstale >= 0 &&
		    (highstale == be32_to_cpu(btp->count) ||
		     mid - lowstale <= highstale - mid)) {
			if (mid - lowstale)
				memmove(&blp[lowstale], &blp[lowstale + 1],
					(mid - lowstale) * sizeof(*blp));
			lfloglow = min(lowstale, lfloglow);
			lfloghigh = max(mid, lfloghigh);
		}
		/*
		 * Move entries toward the high-numbered stale entry.
		 */
		else {
			ASSERT(highstale < be32_to_cpu(btp->count));
			mid++;
			if (highstale - mid)
				memmove(&blp[mid + 1], &blp[mid],
					(highstale - mid) * sizeof(*blp));
			lfloglow = min(mid, lfloglow);
			lfloghigh = max(highstale, lfloghigh);
		}
		be32_add_cpu(&btp->stale, -1);
	}
	/*
	 * Point to the new data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)dup;
	/*
	 * Fill in the leaf entry.
	 */
	blp[mid].hashval = cpu_to_be32(args->hashval);
	blp[mid].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(
				(char *)dep - (char *)hdr));
	xfs_dir2_block_log_leaf(tp, bp, lfloglow, lfloghigh);
	/*
	 * Mark space for the data entry used.
	 */
	error = xfs_dir2_data_use_free(args, bp, dup,
			(xfs_dir2_data_aoff_t)((char *)dup - (char *)hdr),
			(xfs_dir2_data_aoff_t)len, &needlog, &needscan);
	if (error)
		return error;
	/*
	 * Create the new data entry.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	memcpy(dep->name, args->name, args->namelen);
	dp->d_ops->data_put_ftype(dep, args->filetype);
	tagp = dp->d_ops->data_entry_tag_p(dep);
	*tagp = cpu_to_be16((char *)dep - (char *)hdr);
	/*
	 * Clean up the bestfree array and log the header, tail, and entry.
	 */
	if (needscan)
		xfs_dir2_data_freescan(dp, hdr, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(args, bp);
	xfs_dir2_block_log_tail(tp, bp);
	xfs_dir2_data_log_entry(args, bp, dep);
	xfs_dir3_data_check(dp, bp);
	return 0;
}