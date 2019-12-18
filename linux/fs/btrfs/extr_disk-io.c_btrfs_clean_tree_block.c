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
struct extent_buffer {int /*<<< orphan*/  len; int /*<<< orphan*/  bflags; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  dirty_metadata_batch; int /*<<< orphan*/  dirty_metadata_bytes; TYPE_1__* running_transaction; } ;
struct TYPE_2__ {scalar_t__ transid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_write (struct extent_buffer*) ; 
 int /*<<< orphan*/  clear_extent_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_clean_tree_block(struct extent_buffer *buf)
{
	struct btrfs_fs_info *fs_info = buf->fs_info;
	if (btrfs_header_generation(buf) ==
	    fs_info->running_transaction->transid) {
		btrfs_assert_tree_locked(buf);

		if (test_and_clear_bit(EXTENT_BUFFER_DIRTY, &buf->bflags)) {
			percpu_counter_add_batch(&fs_info->dirty_metadata_bytes,
						 -buf->len,
						 fs_info->dirty_metadata_batch);
			/* ugh, clear_extent_buffer_dirty needs to lock the page */
			btrfs_set_lock_blocking_write(buf);
			clear_extent_buffer_dirty(buf);
		}
	}
}