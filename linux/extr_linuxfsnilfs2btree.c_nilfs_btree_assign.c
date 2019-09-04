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
typedef  union nilfs_binfo {int dummy; } nilfs_binfo ;
struct nilfs_btree_path {int dummy; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ NILFS_BMAP_USE_VBN (struct nilfs_bmap*) ; 
 int NILFS_BTREE_LEVEL_DATA ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ buffer_nilfs_node (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_bmap_data_get_key (struct nilfs_bmap*,struct buffer_head*) ; 
 struct nilfs_btree_path* nilfs_btree_alloc_path () ; 
 int nilfs_btree_assign_p (struct nilfs_bmap*,struct nilfs_btree_path*,int,struct buffer_head**,int /*<<< orphan*/ ,union nilfs_binfo*) ; 
 int nilfs_btree_assign_v (struct nilfs_bmap*,struct nilfs_btree_path*,int,struct buffer_head**,int /*<<< orphan*/ ,union nilfs_binfo*) ; 
 int nilfs_btree_do_lookup (struct nilfs_bmap*,struct nilfs_btree_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_free_path (struct nilfs_btree_path*) ; 
 int /*<<< orphan*/  nilfs_btree_node_get_key (struct nilfs_btree_node*,int /*<<< orphan*/ ) ; 
 int nilfs_btree_node_get_level (struct nilfs_btree_node*) ; 

__attribute__((used)) static int nilfs_btree_assign(struct nilfs_bmap *btree,
			      struct buffer_head **bh,
			      sector_t blocknr,
			      union nilfs_binfo *binfo)
{
	struct nilfs_btree_path *path;
	struct nilfs_btree_node *node;
	__u64 key;
	int level, ret;

	path = nilfs_btree_alloc_path();
	if (path == NULL)
		return -ENOMEM;

	if (buffer_nilfs_node(*bh)) {
		node = (struct nilfs_btree_node *)(*bh)->b_data;
		key = nilfs_btree_node_get_key(node, 0);
		level = nilfs_btree_node_get_level(node);
	} else {
		key = nilfs_bmap_data_get_key(btree, *bh);
		level = NILFS_BTREE_LEVEL_DATA;
	}

	ret = nilfs_btree_do_lookup(btree, path, key, NULL, level + 1, 0);
	if (ret < 0) {
		WARN_ON(ret == -ENOENT);
		goto out;
	}

	ret = NILFS_BMAP_USE_VBN(btree) ?
		nilfs_btree_assign_v(btree, path, level, bh, blocknr, binfo) :
		nilfs_btree_assign_p(btree, path, level, bh, blocknr, binfo);

 out:
	nilfs_btree_free_path(path);

	return ret;
}