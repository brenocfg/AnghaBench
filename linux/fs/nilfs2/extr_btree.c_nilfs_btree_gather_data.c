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
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EINVAL ; 
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int nilfs_btree_get_block (struct nilfs_bmap*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap*) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap*) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dkeys (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dptrs (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int,int) ; 

__attribute__((used)) static int nilfs_btree_gather_data(struct nilfs_bmap *btree,
				   __u64 *keys, __u64 *ptrs, int nitems)
{
	struct buffer_head *bh;
	struct nilfs_btree_node *node, *root;
	__le64 *dkeys;
	__le64 *dptrs;
	__u64 ptr;
	int nchildren, ncmax, i, ret;

	root = nilfs_btree_get_root(btree);
	switch (nilfs_btree_height(btree)) {
	case 2:
		bh = NULL;
		node = root;
		ncmax = NILFS_BTREE_ROOT_NCHILDREN_MAX;
		break;
	case 3:
		nchildren = nilfs_btree_node_get_nchildren(root);
		WARN_ON(nchildren > 1);
		ptr = nilfs_btree_node_get_ptr(root, nchildren - 1,
					       NILFS_BTREE_ROOT_NCHILDREN_MAX);
		ret = nilfs_btree_get_block(btree, ptr, &bh);
		if (ret < 0)
			return ret;
		node = (struct nilfs_btree_node *)bh->b_data;
		ncmax = nilfs_btree_nchildren_per_block(btree);
		break;
	default:
		node = NULL;
		return -EINVAL;
	}

	nchildren = nilfs_btree_node_get_nchildren(node);
	if (nchildren < nitems)
		nitems = nchildren;
	dkeys = nilfs_btree_node_dkeys(node);
	dptrs = nilfs_btree_node_dptrs(node, ncmax);
	for (i = 0; i < nitems; i++) {
		keys[i] = le64_to_cpu(dkeys[i]);
		ptrs[i] = le64_to_cpu(dptrs[i]);
	}

	if (bh != NULL)
		brelse(bh);

	return nitems;
}