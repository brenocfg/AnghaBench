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
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int /*<<< orphan*/ * locks; int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_READ_LOCK_BLOCKING ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int PTR_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_node_blockptr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_node_ptr_generation (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_read (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int process_leaf (struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct extent_buffer* read_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 

__attribute__((used)) static int walk_down_tree(struct btrfs_root *root, struct btrfs_path *path,
			  int level, u64 *bytenr, u64 *num_bytes)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct extent_buffer *eb;
	u64 block_bytenr, gen;
	int ret = 0;

	while (level >= 0) {
		if (level) {
			struct btrfs_key first_key;

			block_bytenr = btrfs_node_blockptr(path->nodes[level],
							   path->slots[level]);
			gen = btrfs_node_ptr_generation(path->nodes[level],
							path->slots[level]);
			btrfs_node_key_to_cpu(path->nodes[level], &first_key,
					      path->slots[level]);
			eb = read_tree_block(fs_info, block_bytenr, gen,
					     level - 1, &first_key);
			if (IS_ERR(eb))
				return PTR_ERR(eb);
			if (!extent_buffer_uptodate(eb)) {
				free_extent_buffer(eb);
				return -EIO;
			}
			btrfs_tree_read_lock(eb);
			btrfs_set_lock_blocking_read(eb);
			path->nodes[level-1] = eb;
			path->slots[level-1] = 0;
			path->locks[level-1] = BTRFS_READ_LOCK_BLOCKING;
		} else {
			ret = process_leaf(root, path, bytenr, num_bytes);
			if (ret)
				break;
		}
		level--;
	}
	return ret;
}