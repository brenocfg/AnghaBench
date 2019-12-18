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
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_LARGE_LOW ; 
 int /*<<< orphan*/  NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int nilfs_btree_get_block (struct nilfs_bmap*,scalar_t__,struct buffer_head**) ; 
 struct nilfs_btree_node* nilfs_btree_get_root (struct nilfs_bmap*) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 scalar_t__ nilfs_btree_node_get_key (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 scalar_t__ nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_btree_check_delete(struct nilfs_bmap *btree, __u64 key)
{
	struct buffer_head *bh;
	struct nilfs_btree_node *root, *node;
	__u64 maxkey, nextmaxkey;
	__u64 ptr;
	int nchildren, ret;

	root = nilfs_btree_get_root(btree);
	switch (nilfs_btree_height(btree)) {
	case 2:
		bh = NULL;
		node = root;
		break;
	case 3:
		nchildren = nilfs_btree_node_get_nchildren(root);
		if (nchildren > 1)
			return 0;
		ptr = nilfs_btree_node_get_ptr(root, nchildren - 1,
					       NILFS_BTREE_ROOT_NCHILDREN_MAX);
		ret = nilfs_btree_get_block(btree, ptr, &bh);
		if (ret < 0)
			return ret;
		node = (struct nilfs_btree_node *)bh->b_data;
		break;
	default:
		return 0;
	}

	nchildren = nilfs_btree_node_get_nchildren(node);
	maxkey = nilfs_btree_node_get_key(node, nchildren - 1);
	nextmaxkey = (nchildren > 1) ?
		nilfs_btree_node_get_key(node, nchildren - 2) : 0;
	if (bh != NULL)
		brelse(bh);

	return (maxkey == key) && (nextmaxkey < NILFS_BMAP_LARGE_LOW);
}