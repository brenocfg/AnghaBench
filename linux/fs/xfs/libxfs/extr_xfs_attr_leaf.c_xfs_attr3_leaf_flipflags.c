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
struct xfs_da_args {scalar_t__ blkno; scalar_t__ blkno2; size_t index; size_t index2; int /*<<< orphan*/  dp; int /*<<< orphan*/  trans; scalar_t__ rmtvaluelen; scalar_t__ rmtblkno; int /*<<< orphan*/  geo; } ;
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
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_flipflags (struct xfs_da_args*) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_entryp (struct xfs_attr_leafblock*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (int /*<<< orphan*/ ,struct xfs_attr3_icleaf_hdr*,struct xfs_attr_leafblock*) ; 
 TYPE_1__* xfs_attr3_leaf_name_local (struct xfs_attr_leafblock*,size_t) ; 
 struct xfs_attr_leaf_name_remote* xfs_attr3_leaf_name_remote (struct xfs_attr_leafblock*,size_t) ; 
 int xfs_attr3_leaf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll_inode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_attr3_leaf_flipflags(
	struct xfs_da_args	*args)
{
	struct xfs_attr_leafblock *leaf1;
	struct xfs_attr_leafblock *leaf2;
	struct xfs_attr_leaf_entry *entry1;
	struct xfs_attr_leaf_entry *entry2;
	struct xfs_attr_leaf_name_remote *name_rmt;
	struct xfs_buf		*bp1;
	struct xfs_buf		*bp2;
	int error;
#ifdef DEBUG
	struct xfs_attr3_icleaf_hdr ichdr1;
	struct xfs_attr3_icleaf_hdr ichdr2;
	xfs_attr_leaf_name_local_t *name_loc;
	int namelen1, namelen2;
	char *name1, *name2;
#endif /* DEBUG */

	trace_xfs_attr_leaf_flipflags(args);

	/*
	 * Read the block containing the "old" attr
	 */
	error = xfs_attr3_leaf_read(args->trans, args->dp, args->blkno, -1, &bp1);
	if (error)
		return error;

	/*
	 * Read the block containing the "new" attr, if it is different
	 */
	if (args->blkno2 != args->blkno) {
		error = xfs_attr3_leaf_read(args->trans, args->dp, args->blkno2,
					   -1, &bp2);
		if (error)
			return error;
	} else {
		bp2 = bp1;
	}

	leaf1 = bp1->b_addr;
	entry1 = &xfs_attr3_leaf_entryp(leaf1)[args->index];

	leaf2 = bp2->b_addr;
	entry2 = &xfs_attr3_leaf_entryp(leaf2)[args->index2];

#ifdef DEBUG
	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr1, leaf1);
	ASSERT(args->index < ichdr1.count);
	ASSERT(args->index >= 0);

	xfs_attr3_leaf_hdr_from_disk(args->geo, &ichdr2, leaf2);
	ASSERT(args->index2 < ichdr2.count);
	ASSERT(args->index2 >= 0);

	if (entry1->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr3_leaf_name_local(leaf1, args->index);
		namelen1 = name_loc->namelen;
		name1 = (char *)name_loc->nameval;
	} else {
		name_rmt = xfs_attr3_leaf_name_remote(leaf1, args->index);
		namelen1 = name_rmt->namelen;
		name1 = (char *)name_rmt->name;
	}
	if (entry2->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr3_leaf_name_local(leaf2, args->index2);
		namelen2 = name_loc->namelen;
		name2 = (char *)name_loc->nameval;
	} else {
		name_rmt = xfs_attr3_leaf_name_remote(leaf2, args->index2);
		namelen2 = name_rmt->namelen;
		name2 = (char *)name_rmt->name;
	}
	ASSERT(be32_to_cpu(entry1->hashval) == be32_to_cpu(entry2->hashval));
	ASSERT(namelen1 == namelen2);
	ASSERT(memcmp(name1, name2, namelen1) == 0);
#endif /* DEBUG */

	ASSERT(entry1->flags & XFS_ATTR_INCOMPLETE);
	ASSERT((entry2->flags & XFS_ATTR_INCOMPLETE) == 0);

	entry1->flags &= ~XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp1,
			  XFS_DA_LOGRANGE(leaf1, entry1, sizeof(*entry1)));
	if (args->rmtblkno) {
		ASSERT((entry1->flags & XFS_ATTR_LOCAL) == 0);
		name_rmt = xfs_attr3_leaf_name_remote(leaf1, args->index);
		name_rmt->valueblk = cpu_to_be32(args->rmtblkno);
		name_rmt->valuelen = cpu_to_be32(args->rmtvaluelen);
		xfs_trans_log_buf(args->trans, bp1,
			 XFS_DA_LOGRANGE(leaf1, name_rmt, sizeof(*name_rmt)));
	}

	entry2->flags |= XFS_ATTR_INCOMPLETE;
	xfs_trans_log_buf(args->trans, bp2,
			  XFS_DA_LOGRANGE(leaf2, entry2, sizeof(*entry2)));
	if ((entry2->flags & XFS_ATTR_LOCAL) == 0) {
		name_rmt = xfs_attr3_leaf_name_remote(leaf2, args->index2);
		name_rmt->valueblk = 0;
		name_rmt->valuelen = 0;
		xfs_trans_log_buf(args->trans, bp2,
			 XFS_DA_LOGRANGE(leaf2, name_rmt, sizeof(*name_rmt)));
	}

	/*
	 * Commit the flag value change and start the next trans in series.
	 */
	error = xfs_trans_roll_inode(&args->trans, args->dp);

	return error;
}