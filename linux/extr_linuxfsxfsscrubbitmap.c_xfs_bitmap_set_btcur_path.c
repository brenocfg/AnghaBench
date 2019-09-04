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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
struct xfs_buf {int /*<<< orphan*/  b_bn; } ;
struct xfs_btree_cur {int bc_nlevels; int* bc_ptrs; int /*<<< orphan*/  bc_mp; } ;
struct xfs_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DADDR_TO_FSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_bitmap_set (struct xfs_bitmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_btree_get_block (struct xfs_btree_cur*,int,struct xfs_buf**) ; 

int
xfs_bitmap_set_btcur_path(
	struct xfs_bitmap	*bitmap,
	struct xfs_btree_cur	*cur)
{
	struct xfs_buf		*bp;
	xfs_fsblock_t		fsb;
	int			i;
	int			error;

	for (i = 0; i < cur->bc_nlevels && cur->bc_ptrs[i] == 1; i++) {
		xfs_btree_get_block(cur, i, &bp);
		if (!bp)
			continue;
		fsb = XFS_DADDR_TO_FSB(cur->bc_mp, bp->b_bn);
		error = xfs_bitmap_set(bitmap, fsb, 1);
		if (error)
			return error;
	}

	return 0;
}