#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xfs_da_args {size_t index; int /*<<< orphan*/  dp; int /*<<< orphan*/  trans; int /*<<< orphan*/  geo; int /*<<< orphan*/  blkno; } ;
struct xfs_buf {struct xfs_attr_leafblock* b_addr; } ;
struct xfs_attr_leafblock {int dummy; } ;
struct xfs_attr_leaf_name_remote {int flags; scalar_t__ valuelen; scalar_t__ valueblk; } ;
struct xfs_attr_leaf_entry {int flags; scalar_t__ valuelen; scalar_t__ valueblk; } ;
struct xfs_attr3_icleaf_hdr {size_t count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_ATTR_INCOMPLETE ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (struct xfs_attr_leafblock*,struct xfs_attr_leaf_name_remote*,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_setflag (struct xfs_da_args*) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_entryp (struct xfs_attr_leafblock*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (int /*<<< orphan*/ ,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_name_remote (struct xfs_attr_leafblock*,size_t) ; 
 int xfs_attr3_leaf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_attr3_leaf_setflag(
	struct xfs_da_args	*args)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_attr_leaf_entry *entry;
	struct xfs_attr_leaf_name_remote *name_rmt;
	struct xfs_buf		*bp;
	int error;
#ifdef DEBUG
	struct xfs_attr3_icleaf_hdr ichdr;
#endif

	trace_xfs_attr_leaf_setflag(args);

	/*
	 * Set up the operation.
	 */
	error = xfs_attr3_leaf_read(args->trans, args->dp, args->blkno, -1, &bp);
	if (error)
		return error;

	leaf = bp->b_addr;
#ifdef DEBUG
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(args->index < ichdr.count);
	ASSERT(args->index >= 0);
#endif
	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];

	ASSERT((entry->flags & XFS_ATTR_INCOMPLETE) == 0);
	entry->flags |= XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp,
			XFS_DA_LOGRANGE(leaf, entry, sizeof(*entry)));
	if ((entry->flags & XFS_ATTR_LOCAL) == 0) {
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		name_rmt->valueblk = 0;
		name_rmt->valuelen = 0;
		xfs_trans_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, name_rmt, sizeof(*name_rmt)));
	}

	/*
	 * Commit the flag value change and start the next trans in series.
	 */
	return xfs_trans_roll_inode(&args->trans, args->dp);
}