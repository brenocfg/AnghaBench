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
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_btree_cur {int dummy; } ;
struct xfs_btree_block_change_owner_info {struct list_head* buffer_list; int /*<<< orphan*/  new_owner; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_btree_block_change_owner ; 
 int xfs_btree_visit_blocks (struct xfs_btree_cur*,int /*<<< orphan*/ ,struct xfs_btree_block_change_owner_info*) ; 

int
xfs_btree_change_owner(
	struct xfs_btree_cur	*cur,
	uint64_t		new_owner,
	struct list_head	*buffer_list)
{
	struct xfs_btree_block_change_owner_info	bbcoi;

	bbcoi.new_owner = new_owner;
	bbcoi.buffer_list = buffer_list;

	return xfs_btree_visit_blocks(cur, xfs_btree_block_change_owner,
			&bbcoi);
}