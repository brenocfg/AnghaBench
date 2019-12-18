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
typedef  scalar_t__ xfs_extlen_t ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_btree_count_blocks_helper ; 
 int xfs_btree_visit_blocks (struct xfs_btree_cur*,int /*<<< orphan*/ ,scalar_t__*) ; 

int
xfs_btree_count_blocks(
	struct xfs_btree_cur	*cur,
	xfs_extlen_t		*blocks)
{
	*blocks = 0;
	return xfs_btree_visit_blocks(cur, xfs_btree_count_blocks_helper,
			blocks);
}