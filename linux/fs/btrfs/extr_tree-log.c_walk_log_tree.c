#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct walk_control {int (* process_func ) (struct btrfs_root*,struct extent_buffer*,struct walk_control*,int /*<<< orphan*/ ,int) ;scalar_t__ free; } ;
struct extent_buffer {int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  bflags; } ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct extent_buffer* node; struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {struct extent_buffer** nodes; scalar_t__* slots; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_clean_tree_block (struct extent_buffer*) ; 
 int btrfs_free_and_pin_reserved_extent (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_header_generation (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_write (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_wait_tree_block_writeback (struct extent_buffer*) ; 
 int /*<<< orphan*/  clear_extent_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_get (struct extent_buffer*) ; 
 int stub1 (struct btrfs_root*,struct extent_buffer*,struct walk_control*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int walk_down_log_tree (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int*,struct walk_control*) ; 
 int walk_up_log_tree (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int*,struct walk_control*) ; 

__attribute__((used)) static int walk_log_tree(struct btrfs_trans_handle *trans,
			 struct btrfs_root *log, struct walk_control *wc)
{
	struct btrfs_fs_info *fs_info = log->fs_info;
	int ret = 0;
	int wret;
	int level;
	struct btrfs_path *path;
	int orig_level;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	level = btrfs_header_level(log->node);
	orig_level = level;
	path->nodes[level] = log->node;
	extent_buffer_get(log->node);
	path->slots[level] = 0;

	while (1) {
		wret = walk_down_log_tree(trans, log, path, &level, wc);
		if (wret > 0)
			break;
		if (wret < 0) {
			ret = wret;
			goto out;
		}

		wret = walk_up_log_tree(trans, log, path, &level, wc);
		if (wret > 0)
			break;
		if (wret < 0) {
			ret = wret;
			goto out;
		}
	}

	/* was the root node processed? if not, catch it here */
	if (path->nodes[orig_level]) {
		ret = wc->process_func(log, path->nodes[orig_level], wc,
			 btrfs_header_generation(path->nodes[orig_level]),
			 orig_level);
		if (ret)
			goto out;
		if (wc->free) {
			struct extent_buffer *next;

			next = path->nodes[orig_level];

			if (trans) {
				btrfs_tree_lock(next);
				btrfs_set_lock_blocking_write(next);
				btrfs_clean_tree_block(next);
				btrfs_wait_tree_block_writeback(next);
				btrfs_tree_unlock(next);
			} else {
				if (test_and_clear_bit(EXTENT_BUFFER_DIRTY, &next->bflags))
					clear_extent_buffer_dirty(next);
			}

			WARN_ON(log->root_key.objectid !=
				BTRFS_TREE_LOG_OBJECTID);
			ret = btrfs_free_and_pin_reserved_extent(fs_info,
							next->start, next->len);
			if (ret)
				goto out;
		}
	}

out:
	btrfs_free_path(path);
	return ret;
}