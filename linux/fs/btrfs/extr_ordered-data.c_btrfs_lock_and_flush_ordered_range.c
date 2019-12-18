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
typedef  scalar_t__ u64 ;
struct extent_state {int /*<<< orphan*/  refs; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_ordered_extent {int dummy; } ;
struct btrfs_inode {int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 struct btrfs_ordered_extent* btrfs_lookup_ordered_range (struct btrfs_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_put_ordered_extent (struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  btrfs_start_ordered_extent (int /*<<< orphan*/ *,struct btrfs_ordered_extent*,int) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**) ; 

void btrfs_lock_and_flush_ordered_range(struct extent_io_tree *tree,
					struct btrfs_inode *inode, u64 start,
					u64 end,
					struct extent_state **cached_state)
{
	struct btrfs_ordered_extent *ordered;
	struct extent_state *cache = NULL;
	struct extent_state **cachedp = &cache;

	if (cached_state)
		cachedp = cached_state;

	while (1) {
		lock_extent_bits(tree, start, end, cachedp);
		ordered = btrfs_lookup_ordered_range(inode, start,
						     end - start + 1);
		if (!ordered) {
			/*
			 * If no external cached_state has been passed then
			 * decrement the extra ref taken for cachedp since we
			 * aren't exposing it outside of this function
			 */
			if (!cached_state)
				refcount_dec(&cache->refs);
			break;
		}
		unlock_extent_cached(tree, start, end, cachedp);
		btrfs_start_ordered_extent(&inode->vfs_inode, ordered, 1);
		btrfs_put_ordered_extent(ordered);
	}
}