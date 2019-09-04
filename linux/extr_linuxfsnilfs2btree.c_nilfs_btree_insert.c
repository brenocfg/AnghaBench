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
struct nilfs_btree_path {int dummy; } ;
struct nilfs_bmap_stats {int /*<<< orphan*/  bs_nblocks; } ;
struct nilfs_bmap {int /*<<< orphan*/  b_inode; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NILFS_BTREE_LEVEL_NODE_MIN ; 
 struct nilfs_btree_path* nilfs_btree_alloc_path () ; 
 int /*<<< orphan*/  nilfs_btree_commit_insert (struct nilfs_bmap*,struct nilfs_btree_path*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nilfs_btree_do_lookup (struct nilfs_bmap*,struct nilfs_btree_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_free_path (struct nilfs_btree_path*) ; 
 int nilfs_btree_prepare_insert (struct nilfs_bmap*,struct nilfs_btree_path*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nilfs_bmap_stats*) ; 
 int /*<<< orphan*/  nilfs_inode_add_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_btree_insert(struct nilfs_bmap *btree, __u64 key, __u64 ptr)
{
	struct nilfs_btree_path *path;
	struct nilfs_bmap_stats stats;
	int level, ret;

	path = nilfs_btree_alloc_path();
	if (path == NULL)
		return -ENOMEM;

	ret = nilfs_btree_do_lookup(btree, path, key, NULL,
				    NILFS_BTREE_LEVEL_NODE_MIN, 0);
	if (ret != -ENOENT) {
		if (ret == 0)
			ret = -EEXIST;
		goto out;
	}

	ret = nilfs_btree_prepare_insert(btree, path, &level, key, ptr, &stats);
	if (ret < 0)
		goto out;
	nilfs_btree_commit_insert(btree, path, level, key, ptr);
	nilfs_inode_add_blocks(btree->b_inode, stats.bs_nblocks);

 out:
	nilfs_btree_free_path(path);
	return ret;
}