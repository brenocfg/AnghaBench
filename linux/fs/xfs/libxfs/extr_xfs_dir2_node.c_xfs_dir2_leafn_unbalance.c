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
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct TYPE_19__ {TYPE_4__* args; } ;
typedef  TYPE_2__ xfs_da_state_t ;
struct TYPE_20__ {scalar_t__ magic; TYPE_6__* bp; void* hashval; } ;
typedef  TYPE_3__ xfs_da_state_blk_t ;
struct TYPE_21__ {struct xfs_inode* dp; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct xfs_inode {TYPE_1__* d_ops; } ;
struct xfs_dir3_icleaf_hdr {int count; scalar_t__ stale; } ;
struct xfs_dir2_leaf_entry {int /*<<< orphan*/  hashval; } ;
struct TYPE_22__ {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* leaf_hdr_to_disk ) (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* leaf_hdr_from_disk ) (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_LEAFN_MAGIC ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct xfs_dir3_icleaf_hdr*,int /*<<< orphan*/ *) ; 
 struct xfs_dir2_leaf_entry* stub3 (int /*<<< orphan*/ *) ; 
 struct xfs_dir2_leaf_entry* stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ; 
 scalar_t__ xfs_dir2_leafn_order (struct xfs_inode*,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_check (struct xfs_inode*,TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_compact (TYPE_4__*,struct xfs_dir3_icleaf_hdr*,TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_header (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir3_leafn_moveents (TYPE_4__*,TYPE_6__*,struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf_entry*,int /*<<< orphan*/ ,TYPE_6__*,struct xfs_dir3_icleaf_hdr*,struct xfs_dir2_leaf_entry*,int,int) ; 

void
xfs_dir2_leafn_unbalance(
	xfs_da_state_t		*state,		/* cursor */
	xfs_da_state_blk_t	*drop_blk,	/* dead block */
	xfs_da_state_blk_t	*save_blk)	/* surviving block */
{
	xfs_da_args_t		*args;		/* operation arguments */
	xfs_dir2_leaf_t		*drop_leaf;	/* dead leaf structure */
	xfs_dir2_leaf_t		*save_leaf;	/* surviving leaf structure */
	struct xfs_dir3_icleaf_hdr savehdr;
	struct xfs_dir3_icleaf_hdr drophdr;
	struct xfs_dir2_leaf_entry *sents;
	struct xfs_dir2_leaf_entry *dents;
	struct xfs_inode	*dp = state->args->dp;

	args = state->args;
	ASSERT(drop_blk->magic == XFS_DIR2_LEAFN_MAGIC);
	ASSERT(save_blk->magic == XFS_DIR2_LEAFN_MAGIC);
	drop_leaf = drop_blk->bp->b_addr;
	save_leaf = save_blk->bp->b_addr;

	dp->d_ops->leaf_hdr_from_disk(&savehdr, save_leaf);
	dp->d_ops->leaf_hdr_from_disk(&drophdr, drop_leaf);
	sents = dp->d_ops->leaf_ents_p(save_leaf);
	dents = dp->d_ops->leaf_ents_p(drop_leaf);

	/*
	 * If there are any stale leaf entries, take this opportunity
	 * to purge them.
	 */
	if (drophdr.stale)
		xfs_dir3_leaf_compact(args, &drophdr, drop_blk->bp);
	if (savehdr.stale)
		xfs_dir3_leaf_compact(args, &savehdr, save_blk->bp);

	/*
	 * Move the entries from drop to the appropriate end of save.
	 */
	drop_blk->hashval = be32_to_cpu(dents[drophdr.count - 1].hashval);
	if (xfs_dir2_leafn_order(dp, save_blk->bp, drop_blk->bp))
		xfs_dir3_leafn_moveents(args, drop_blk->bp, &drophdr, dents, 0,
					save_blk->bp, &savehdr, sents, 0,
					drophdr.count);
	else
		xfs_dir3_leafn_moveents(args, drop_blk->bp, &drophdr, dents, 0,
					save_blk->bp, &savehdr, sents,
					savehdr.count, drophdr.count);
	save_blk->hashval = be32_to_cpu(sents[savehdr.count - 1].hashval);

	/* log the changes made when moving the entries */
	dp->d_ops->leaf_hdr_to_disk(save_leaf, &savehdr);
	dp->d_ops->leaf_hdr_to_disk(drop_leaf, &drophdr);
	xfs_dir3_leaf_log_header(args, save_blk->bp);
	xfs_dir3_leaf_log_header(args, drop_blk->bp);

	xfs_dir3_leaf_check(dp, save_blk->bp);
	xfs_dir3_leaf_check(dp, drop_blk->bp);
}