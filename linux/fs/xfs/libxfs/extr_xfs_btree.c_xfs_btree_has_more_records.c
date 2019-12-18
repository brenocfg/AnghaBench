#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {scalar_t__* bc_ptrs; int bc_flags; } ;
struct TYPE_5__ {scalar_t__ bb_rightsib; } ;
struct TYPE_4__ {scalar_t__ bb_rightsib; } ;
struct TYPE_6__ {TYPE_2__ s; TYPE_1__ l; } ;
struct xfs_btree_block {TYPE_3__ bb_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLAGBLOCK ; 
 int /*<<< orphan*/  NULLFSBLOCK ; 
 int XFS_BTREE_LONG_PTRS ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct xfs_btree_block* xfs_btree_get_block (struct xfs_btree_cur*,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 scalar_t__ xfs_btree_get_numrecs (struct xfs_btree_block*) ; 

bool
xfs_btree_has_more_records(
	struct xfs_btree_cur	*cur)
{
	struct xfs_btree_block	*block;
	struct xfs_buf		*bp;

	block = xfs_btree_get_block(cur, 0, &bp);

	/* There are still records in this block. */
	if (cur->bc_ptrs[0] < xfs_btree_get_numrecs(block))
		return true;

	/* There are more record blocks. */
	if (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		return block->bb_u.l.bb_rightsib != cpu_to_be64(NULLFSBLOCK);
	else
		return block->bb_u.s.bb_rightsib != cpu_to_be32(NULLAGBLOCK);
}