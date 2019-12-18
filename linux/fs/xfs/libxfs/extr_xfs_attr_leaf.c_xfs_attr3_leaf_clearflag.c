#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int namelen; scalar_t__ nameval; } ;
typedef  TYPE_1__ xfs_attr_leaf_name_local_t ;
struct xfs_da_args {size_t index; scalar_t__ hashval; int namelen; int /*<<< orphan*/  dp; int /*<<< orphan*/  trans; scalar_t__ rmtvaluelen; scalar_t__ rmtblkno; int /*<<< orphan*/  name; int /*<<< orphan*/  geo; int /*<<< orphan*/  blkno; } ;
struct xfs_buf {struct xfs_attr_leafblock* b_addr; } ;
struct xfs_attr_leafblock {int dummy; } ;
struct xfs_attr_leaf_name_remote {int flags; int namelen; void* valuelen; void* valueblk; int /*<<< orphan*/  hashval; scalar_t__ name; } ;
struct xfs_attr_leaf_entry {int flags; int namelen; void* valuelen; void* valueblk; int /*<<< orphan*/  hashval; scalar_t__ name; } ;
struct xfs_attr3_icleaf_hdr {size_t count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_ATTR_INCOMPLETE ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (struct xfs_attr_leafblock*,struct xfs_attr_leaf_name_remote*,int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_clearflag (struct xfs_da_args*) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_entryp (struct xfs_attr_leafblock*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (int /*<<< orphan*/ ,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 TYPE_1__* xfs_attr3_leaf_name_local (struct xfs_attr_leafblock*,size_t) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_name_remote (struct xfs_attr_leafblock*,size_t) ; 
 int xfs_attr3_leaf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_attr3_leaf_clearflag(
	struct xfs_da_args	*args)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_attr_leaf_entry *entry;
	struct xfs_attr_leaf_name_remote *name_rmt;
	struct xfs_buf		*bp;
	int			error;
#ifdef DEBUG
	struct xfs_attr3_icleaf_hdr ichdr;
	xfs_attr_leaf_name_local_t *name_loc;
	int namelen;
	char *name;
#endif /* DEBUG */

	trace_xfs_attr_leaf_clearflag(args);
	/*
	 * Set up the operation.
	 */
	error = xfs_attr3_leaf_read(args->trans, args->dp, args->blkno, -1, &bp);
	if (error)
		return error;

	leaf = bp->b_addr;
	entry = &xfs_attr3_leaf_entryp(leaf)[args->index];
	ASSERT(entry->flags & XFS_ATTR_INCOMPLETE);

#ifdef DEBUG
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr, leaf);
	ASSERT(args->index < ichdr.count);
	ASSERT(args->index >= 0);

	if (entry->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr3_leaf_name_local(leaf, args->index);
		namelen = name_loc->namelen;
		name = (char *)name_loc->nameval;
	} else {
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		namelen = name_rmt->namelen;
		name = (char *)name_rmt->name;
	}
	ASSERT(be32_to_cpu(entry->hashval) == args->hashval);
	ASSERT(namelen == args->namelen);
	ASSERT(memcmp(name, args->name, namelen) == 0);
#endif /* DEBUG */

	entry->flags &= ~XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, entry, sizeof(*entry)));

	if (args->rmtblkno) {
		ASSERT((entry->flags & XFS_ATTR_LOCAL) == 0);
		name_rmt = xfs_attr3_leaf_name_remote(leaf, args->index);
		name_rmt->valueblk = cpu_to_be32(args->rmtblkno);
		name_rmt->valuelen = cpu_to_be32(args->rmtvaluelen);
		xfs_trans_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, name_rmt, sizeof(*name_rmt)));
	}

	/*
	 * Commit the flag value change and start the next trans in series.
	 */
	return xfs_trans_roll_inode(&args->trans, args->dp);
}