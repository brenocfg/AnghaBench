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
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int bc_flags; } ;
struct xfs_btree_block {int dummy; } ;

/* Variables and functions */
 int XFS_BTREE_LONG_PTRS ; 
 int xfs_btree_check_lblock (struct xfs_btree_cur*,struct xfs_btree_block*,int,struct xfs_buf*) ; 
 int xfs_btree_check_sblock (struct xfs_btree_cur*,struct xfs_btree_block*,int,struct xfs_buf*) ; 

int
xfs_btree_check_block(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	struct xfs_btree_block	*block,	/* generic btree block pointer */
	int			level,	/* level of the btree block */
	struct xfs_buf		*bp)	/* buffer containing block, if any */
{
	if (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		return xfs_btree_check_lblock(cur, block, level, bp);
	else
		return xfs_btree_check_sblock(cur, block, level, bp);
}