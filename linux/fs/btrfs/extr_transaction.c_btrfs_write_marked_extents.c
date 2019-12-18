#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_fs_info {TYPE_2__* btree_inode; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {struct address_space* i_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  sync_writers; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENT_NEED_WAIT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int convert_extent_bit (struct extent_io_tree*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,struct extent_state**) ; 
 int filemap_fdatawait_range (struct address_space*,scalar_t__,scalar_t__) ; 
 int filemap_fdatawrite_range (struct address_space*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  find_first_extent_bit (struct extent_io_tree*,scalar_t__,scalar_t__*,scalar_t__*,int,struct extent_state**) ; 
 int /*<<< orphan*/  free_extent_state (struct extent_state*) ; 

int btrfs_write_marked_extents(struct btrfs_fs_info *fs_info,
			       struct extent_io_tree *dirty_pages, int mark)
{
	int err = 0;
	int werr = 0;
	struct address_space *mapping = fs_info->btree_inode->i_mapping;
	struct extent_state *cached_state = NULL;
	u64 start = 0;
	u64 end;

	atomic_inc(&BTRFS_I(fs_info->btree_inode)->sync_writers);
	while (!find_first_extent_bit(dirty_pages, start, &start, &end,
				      mark, &cached_state)) {
		bool wait_writeback = false;

		err = convert_extent_bit(dirty_pages, start, end,
					 EXTENT_NEED_WAIT,
					 mark, &cached_state);
		/*
		 * convert_extent_bit can return -ENOMEM, which is most of the
		 * time a temporary error. So when it happens, ignore the error
		 * and wait for writeback of this range to finish - because we
		 * failed to set the bit EXTENT_NEED_WAIT for the range, a call
		 * to __btrfs_wait_marked_extents() would not know that
		 * writeback for this range started and therefore wouldn't
		 * wait for it to finish - we don't want to commit a
		 * superblock that points to btree nodes/leafs for which
		 * writeback hasn't finished yet (and without errors).
		 * We cleanup any entries left in the io tree when committing
		 * the transaction (through extent_io_tree_release()).
		 */
		if (err == -ENOMEM) {
			err = 0;
			wait_writeback = true;
		}
		if (!err)
			err = filemap_fdatawrite_range(mapping, start, end);
		if (err)
			werr = err;
		else if (wait_writeback)
			werr = filemap_fdatawait_range(mapping, start, end);
		free_extent_state(cached_state);
		cached_state = NULL;
		cond_resched();
		start = end + 1;
	}
	atomic_dec(&BTRFS_I(fs_info->btree_inode)->sync_writers);
	return werr;
}