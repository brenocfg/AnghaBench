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
struct nilfs_btree_path {int bp_index; int /*<<< orphan*/ * bp_bh; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 scalar_t__ nilfs_btree_bad_node (struct nilfs_bmap const*,struct nilfs_btree_node*,int) ; 
 int nilfs_btree_get_block (struct nilfs_bmap const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap const*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap const*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_key (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_level (struct nilfs_btree_node*) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int,int) ; 

__attribute__((used)) static int nilfs_btree_do_lookup_last(const struct nilfs_bmap *btree,
				      struct nilfs_btree_path *path,
				      __u64 *keyp, __u64 *ptrp)
{
	struct nilfs_btree_node *node;
	__u64 ptr;
	int index, level, ncmax, ret;

	node = nilfs_btree_get_root(btree);
	index = nilfs_btree_node_get_nchildren(node) - 1;
	if (index < 0)
		return -ENOENT;
	level = nilfs_btree_node_get_level(node);
	ptr = nilfs_btree_node_get_ptr(node, index,
				       NILFS_BTREE_ROOT_NCHILDREN_MAX);
	path[level].bp_bh = NULL;
	path[level].bp_index = index;
	ncmax = nilfs_btree_nchildren_per_block(btree);

	for (level--; level > 0; level--) {
		ret = nilfs_btree_get_block(btree, ptr, &path[level].bp_bh);
		if (ret < 0)
			return ret;
		node = nilfs_btree_get_nonroot_node(path, level);
		if (nilfs_btree_bad_node(btree, node, level))
			return -EINVAL;
		index = nilfs_btree_node_get_nchildren(node) - 1;
		ptr = nilfs_btree_node_get_ptr(node, index, ncmax);
		path[level].bp_index = index;
	}

	if (keyp != NULL)
		*keyp = nilfs_btree_node_get_key(node, index);
	if (ptrp != NULL)
		*ptrp = ptr;

	return 0;
}