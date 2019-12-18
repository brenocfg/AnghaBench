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
struct nilfs_btree_path {int /*<<< orphan*/  bp_index; int /*<<< orphan*/  bp_bh; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap*) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_btree_node_delete (struct nilfs_btree_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_key (struct nilfs_btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_promote_key (struct nilfs_bmap*,struct nilfs_btree_path*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_btree_do_delete(struct nilfs_bmap *btree,
				  struct nilfs_btree_path *path,
				  int level, __u64 *keyp, __u64 *ptrp)
{
	struct nilfs_btree_node *node;
	int ncblk;

	if (level < nilfs_btree_height(btree) - 1) {
		node = nilfs_btree_get_nonroot_node(path, level);
		ncblk = nilfs_btree_nchildren_per_block(btree);
		nilfs_btree_node_delete(node, path[level].bp_index,
					keyp, ptrp, ncblk);
		if (!buffer_dirty(path[level].bp_bh))
			mark_buffer_dirty(path[level].bp_bh);
		if (path[level].bp_index == 0)
			nilfs_btree_promote_key(btree, path, level + 1,
				nilfs_btree_node_get_key(node, 0));
	} else {
		node = nilfs_btree_get_root(btree);
		nilfs_btree_node_delete(node, path[level].bp_index,
					keyp, ptrp,
					NILFS_BTREE_ROOT_NCHILDREN_MAX);
	}
}