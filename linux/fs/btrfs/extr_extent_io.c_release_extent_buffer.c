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
struct extent_buffer {int start; int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  bflags; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  refs; } ;
struct btrfs_fs_info {int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  buffer_radix; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_IN_TREE ; 
 int /*<<< orphan*/  EXTENT_BUFFER_UNMAPPED ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __free_extent_buffer (struct extent_buffer*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_release_extent_buffer_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_release_extent_buffer_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int release_extent_buffer(struct extent_buffer *eb)
{
	lockdep_assert_held(&eb->refs_lock);

	WARN_ON(atomic_read(&eb->refs) == 0);
	if (atomic_dec_and_test(&eb->refs)) {
		if (test_and_clear_bit(EXTENT_BUFFER_IN_TREE, &eb->bflags)) {
			struct btrfs_fs_info *fs_info = eb->fs_info;

			spin_unlock(&eb->refs_lock);

			spin_lock(&fs_info->buffer_lock);
			radix_tree_delete(&fs_info->buffer_radix,
					  eb->start >> PAGE_SHIFT);
			spin_unlock(&fs_info->buffer_lock);
		} else {
			spin_unlock(&eb->refs_lock);
		}

		/* Should be safe to release our pages at this point */
		btrfs_release_extent_buffer_pages(eb);
#ifdef CONFIG_BTRFS_FS_RUN_SANITY_TESTS
		if (unlikely(test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags))) {
			__free_extent_buffer(eb);
			return 1;
		}
#endif
		call_rcu(&eb->rcu_head, btrfs_release_extent_buffer_rcu);
		return 1;
	}
	spin_unlock(&eb->refs_lock);

	return 0;
}