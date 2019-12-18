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
struct nilfs_btree_path {int bp_index; int /*<<< orphan*/ * bp_sib_bh; int /*<<< orphan*/ * bp_bh; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_btnode_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_btree_do_delete (struct nilfs_bmap*,struct nilfs_btree_path*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_sib_node (struct nilfs_btree_path*,int) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap*) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_move_left (struct nilfs_btree_node*,struct nilfs_btree_node*,int,int,int) ; 

__attribute__((used)) static void nilfs_btree_concat_left(struct nilfs_bmap *btree,
				    struct nilfs_btree_path *path,
				    int level, __u64 *keyp, __u64 *ptrp)
{
	struct nilfs_btree_node *node, *left;
	int n, ncblk;

	nilfs_btree_do_delete(btree, path, level, keyp, ptrp);

	node = nilfs_btree_get_nonroot_node(path, level);
	left = nilfs_btree_get_sib_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = nilfs_btree_node_get_nchildren(node);

	nilfs_btree_node_move_left(left, node, n, ncblk, ncblk);

	if (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	nilfs_btnode_delete(path[level].bp_bh);
	path[level].bp_bh = path[level].bp_sib_bh;
	path[level].bp_sib_bh = NULL;
	path[level].bp_index += nilfs_btree_node_get_nchildren(left);
}