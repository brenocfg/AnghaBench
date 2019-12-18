#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_21__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_sf_hdr_t ;
struct TYPE_22__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
struct TYPE_23__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_4__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_24__ {int /*<<< orphan*/  stale; } ;
typedef  TYPE_5__ xfs_dir2_block_tail_t ;
struct TYPE_25__ {int /*<<< orphan*/  geo; int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* data_entsize ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 int XFS_IFORK_DSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_removename (TYPE_6__*) ; 
 TYPE_3__* xfs_dir2_block_leaf_p (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_leaf (int /*<<< orphan*/ *,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_tail (int /*<<< orphan*/ *,struct xfs_buf*) ; 
 int xfs_dir2_block_lookup_int (TYPE_6__*,struct xfs_buf**,int*) ; 
 int xfs_dir2_block_sfsize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* xfs_dir2_block_tail_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_dir2_block_to_sf (TYPE_6__*,struct xfs_buf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (TYPE_6__*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (TYPE_6__*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir3_data_check (TYPE_2__*,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_block_removename(
	xfs_da_args_t		*args)		/* directory operation args */
{
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf pointer */
	struct xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	int			ent;		/* block leaf entry index */
	int			error;		/* error return value */
	int			needlog;	/* need to log block header */
	int			needscan;	/* need to fixup bestfree */
	xfs_dir2_sf_hdr_t	sfh;		/* shortform header */
	int			size;		/* shortform size */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_block_removename(args);

	/*
	 * Look up the entry in the block.  Gets the buffer and entry index.
	 * It will always be there, the vnodeops level does a lookup first.
	 */
	if ((error = xfs_dir2_block_lookup_int(args, &bp, &ent))) {
		return error;
	}
	dp = args->dp;
	tp = args->trans;
	hdr = bp->b_addr;
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Point to the data entry using the leaf entry.
	 */
	dep = (xfs_dir2_data_entry_t *)((char *)hdr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(blp[ent].address)));
	/*
	 * Mark the data entry's space free.
	 */
	needlog = needscan = 0;
	xfs_dir2_data_make_free(args, bp,
		(xfs_dir2_data_aoff_t)((char *)dep - (char *)hdr),
		dp->d_ops->data_entsize(dep->namelen), &needlog, &needscan);
	/*
	 * Fix up the block tail.
	 */
	be32_add_cpu(&btp->stale, 1);
	xfs_dir2_block_log_tail(tp, bp);
	/*
	 * Remove the leaf entry by marking it stale.
	 */
	blp[ent].address = cpu_to_be32(XFS_DIR2_NULL_DATAPTR);
	xfs_dir2_block_log_leaf(tp, bp, ent, ent);
	/*
	 * Fix up bestfree, log the header if necessary.
	 */
	if (needscan)
		xfs_dir2_data_freescan(dp, hdr, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(args, bp);
	xfs_dir3_data_check(dp, bp);
	/*
	 * See if the size as a shortform is good enough.
	 */
	size = xfs_dir2_block_sfsize(dp, hdr, &sfh);
	if (size > XFS_IFORK_DSIZE(dp))
		return 0;

	/*
	 * If it works, do the conversion.
	 */
	return xfs_dir2_block_to_sf(args, bp, size, &sfh);
}