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
struct nilfs_btree_path {int /*<<< orphan*/ * bp_bh; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  nilfs_btnode_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_btree_do_delete (struct nilfs_bmap*,struct nilfs_btree_path*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_btree_node_delete (struct nilfs_btree_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_move_left (struct nilfs_btree_node*,struct nilfs_btree_node*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_level (struct nilfs_btree_node*,int) ; 

__attribute__((used)) static void nilfs_btree_shrink(struct nilfs_bmap *btree,
			       struct nilfs_btree_path *path,
			       int level, __u64 *keyp, __u64 *ptrp)
{
	struct nilfs_btree_node *root, *child;
	int n, ncblk;

	nilfs_btree_do_delete(btree, path, level, keyp, ptrp);

	root = nilfs_btree_get_root(btree);
	child = nilfs_btree_get_nonroot_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	nilfs_btree_node_delete(root, 0, NULL, NULL,
				NILFS_BTREE_ROOT_NCHILDREN_MAX);
	nilfs_btree_node_set_level(root, level);
	n = nilfs_btree_node_get_nchildren(child);
	nilfs_btree_node_move_left(root, child, n,
				   NILFS_BTREE_ROOT_NCHILDREN_MAX, ncblk);

	nilfs_btnode_delete(path[level].bp_bh);
	path[level].bp_bh = NULL;
}