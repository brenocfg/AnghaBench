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
struct nilfs_btree_path {scalar_t__ bp_index; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_BMAP_INVALID_PTR ; 
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 struct nilfs_btree_node* nilfs_btree_get_node (struct nilfs_bmap const*,struct nilfs_btree_path const*,int,int*) ; 
 int nilfs_btree_height (struct nilfs_bmap const*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_ptr (struct nilfs_btree_node*,scalar_t__,int) ; 

__attribute__((used)) static __u64 nilfs_btree_find_near(const struct nilfs_bmap *btree,
				   const struct nilfs_btree_path *path)
{
	struct nilfs_btree_node *node;
	int level, ncmax;

	if (path == NULL)
		return NILFS_BMAP_INVALID_PTR;

	/* left sibling */
	level = NILFS_BTREE_LEVEL_NODE_MIN;
	if (path[level].bp_index > 0) {
		node = nilfs_btree_get_node(btree, path, level, &ncmax);
		return nilfs_btree_node_get_ptr(node,
						path[level].bp_index - 1,
						ncmax);
	}

	/* parent */
	level = NILFS_BTREE_LEVEL_NODE_MIN + 1;
	if (level <= nilfs_btree_height(btree) - 1) {
		node = nilfs_btree_get_node(btree, path, level, &ncmax);
		return nilfs_btree_node_get_ptr(node, path[level].bp_index,
						ncmax);
	}

	return NILFS_BMAP_INVALID_PTR;
}