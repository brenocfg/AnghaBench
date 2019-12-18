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
struct walk_control {int free; int /*<<< orphan*/  process_func; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  node; int /*<<< orphan*/  dirty_log_pages; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int EXTENT_DIRTY ; 
 int EXTENT_NEED_WAIT ; 
 int EXTENT_NEW ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int /*<<< orphan*/  btrfs_handle_fs_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_extent_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_root*) ; 
 int /*<<< orphan*/  process_one_buffer ; 
 int walk_log_tree (struct btrfs_trans_handle*,struct btrfs_root*,struct walk_control*) ; 

__attribute__((used)) static void free_log_tree(struct btrfs_trans_handle *trans,
			  struct btrfs_root *log)
{
	int ret;
	struct walk_control wc = {
		.free = 1,
		.process_func = process_one_buffer
	};

	ret = walk_log_tree(trans, log, &wc);
	if (ret) {
		if (trans)
			btrfs_abort_transaction(trans, ret);
		else
			btrfs_handle_fs_error(log->fs_info, ret, NULL);
	}

	clear_extent_bits(&log->dirty_log_pages, 0, (u64)-1,
			  EXTENT_DIRTY | EXTENT_NEW | EXTENT_NEED_WAIT);
	free_extent_buffer(log->node);
	kfree(log);
}