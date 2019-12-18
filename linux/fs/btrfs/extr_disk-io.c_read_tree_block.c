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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 struct extent_buffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int btree_read_extent_buffer_pages (struct extent_buffer*,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 
 struct extent_buffer* btrfs_find_create_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_buffer_stale (struct extent_buffer*) ; 

struct extent_buffer *read_tree_block(struct btrfs_fs_info *fs_info, u64 bytenr,
				      u64 parent_transid, int level,
				      struct btrfs_key *first_key)
{
	struct extent_buffer *buf = NULL;
	int ret;

	buf = btrfs_find_create_tree_block(fs_info, bytenr);
	if (IS_ERR(buf))
		return buf;

	ret = btree_read_extent_buffer_pages(buf, parent_transid,
					     level, first_key);
	if (ret) {
		free_extent_buffer_stale(buf);
		return ERR_PTR(ret);
	}
	return buf;

}