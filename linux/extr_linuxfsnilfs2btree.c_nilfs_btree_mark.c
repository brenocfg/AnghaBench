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
struct nilfs_bmap {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_bmap_dirty (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_bmap_set_dirty (struct nilfs_bmap*) ; 
 struct nilfs_btree_path* nilfs_btree_alloc_path () ; 
 int nilfs_btree_do_lookup (struct nilfs_bmap*,struct nilfs_btree_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_free_path (struct nilfs_btree_path*) ; 
 int nilfs_btree_get_block (struct nilfs_bmap*,int /*<<< orphan*/ ,struct buffer_head**) ; 

__attribute__((used)) static int nilfs_btree_mark(struct nilfs_bmap *btree, __u64 key, int level)
{
	struct buffer_head *bh;
	struct nilfs_btree_path *path;
	__u64 ptr;
	int ret;

	path = nilfs_btree_alloc_path();
	if (path == NULL)
		return -ENOMEM;

	ret = nilfs_btree_do_lookup(btree, path, key, &ptr, level + 1, 0);
	if (ret < 0) {
		WARN_ON(ret == -ENOENT);
		goto out;
	}
	ret = nilfs_btree_get_block(btree, ptr, &bh);
	if (ret < 0) {
		WARN_ON(ret == -ENOENT);
		goto out;
	}

	if (!buffer_dirty(bh))
		mark_buffer_dirty(bh);
	brelse(bh);
	if (!nilfs_bmap_dirty(btree))
		nilfs_bmap_set_dirty(btree);

 out:
	nilfs_btree_free_path(path);
	return ret;
}