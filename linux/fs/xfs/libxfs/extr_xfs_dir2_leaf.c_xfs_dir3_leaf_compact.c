#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dir2_leaf_t ;
struct TYPE_7__ {struct xfs_inode* dp; } ;
typedef  TYPE_2__ xfs_da_args_t ;
struct xfs_inode {TYPE_1__* d_ops; } ;
struct xfs_dir3_icleaf_hdr {int stale; int count; } ;
struct xfs_dir2_leaf_entry {scalar_t__ address; } ;
struct xfs_buf {int /*<<< orphan*/ * b_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* leaf_hdr_to_disk ) (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ;struct xfs_dir2_leaf_entry* (* leaf_ents_p ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct xfs_dir2_leaf_entry* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct xfs_dir3_icleaf_hdr*) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_ents (TYPE_2__*,struct xfs_buf*,int,int) ; 
 int /*<<< orphan*/  xfs_dir3_leaf_log_header (TYPE_2__*,struct xfs_buf*) ; 

void
xfs_dir3_leaf_compact(
	xfs_da_args_t	*args,		/* operation arguments */
	struct xfs_dir3_icleaf_hdr *leafhdr,
	struct xfs_buf	*bp)		/* leaf buffer */
{
	int		from;		/* source leaf index */
	xfs_dir2_leaf_t	*leaf;		/* leaf structure */
	int		loglow;		/* first leaf entry to log */
	int		to;		/* target leaf index */
	struct xfs_dir2_leaf_entry *ents;
	struct xfs_inode *dp = args->dp;

	leaf = bp->b_addr;
	if (!leafhdr->stale)
		return;

	/*
	 * Compress out the stale entries in place.
	 */
	ents = dp->d_ops->leaf_ents_p(leaf);
	for (from = to = 0, loglow = -1; from < leafhdr->count; from++) {
		if (ents[from].address == cpu_to_be32(XFS_DIR2_NULL_DATAPTR))
			continue;
		/*
		 * Only actually copy the entries that are different.
		 */
		if (from > to) {
			if (loglow == -1)
				loglow = to;
			ents[to] = ents[from];
		}
		to++;
	}
	/*
	 * Update and log the header, log the leaf entries.
	 */
	ASSERT(leafhdr->stale == from - to);
	leafhdr->count -= leafhdr->stale;
	leafhdr->stale = 0;

	dp->d_ops->leaf_hdr_to_disk(leaf, leafhdr);
	xfs_dir3_leaf_log_header(args, bp);
	if (loglow != -1)
		xfs_dir3_leaf_log_ents(args, bp, loglow, to - 1);
}