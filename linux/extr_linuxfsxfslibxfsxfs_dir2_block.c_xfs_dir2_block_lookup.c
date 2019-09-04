#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* d_ops; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_15__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_hdr_t ;
struct TYPE_16__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; } ;
typedef  TYPE_4__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
struct TYPE_17__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  filetype; int /*<<< orphan*/  inumber; int /*<<< orphan*/  geo; TYPE_2__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* data_get_ftype ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_lookup (TYPE_5__*) ; 
 TYPE_3__* xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int xfs_dir2_block_lookup_int (TYPE_5__*,struct xfs_buf**,int*) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir3_data_check (TYPE_2__*,struct xfs_buf*) ; 
 int xfs_dir_cilookup_result (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,struct xfs_buf*) ; 

int						/* error */
xfs_dir2_block_lookup(
	xfs_da_args_t		*args)		/* dir lookup arguments */
{
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	struct xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	int			ent;		/* entry index */
	int			error;		/* error return value */

	trace_xfs_dir2_block_lookup(args);

	/*
	 * Get the buffer, look up the entry.
	 * If not found (ENOENT) then return, have no buffer.
	 */
	if ((error = xfs_dir2_block_lookup_int(args, &bp, &ent)))
		return error;
	dp = args->dp;
	hdr = bp->b_addr;
	xfs_dir3_data_check(dp, bp);
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Get the offset from the leaf entry, to point to the data.
	 */
	dep = (xfs_dir2_data_entry_t *)((char *)hdr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(blp[ent].address)));
	/*
	 * Fill in inode number, CI name if appropriate, release the block.
	 */
	args->inumber = be64_to_cpu(dep->inumber);
	args->filetype = dp->d_ops->data_get_ftype(dep);
	error = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	xfs_trans_brelse(args->trans, bp);
	return error;
}