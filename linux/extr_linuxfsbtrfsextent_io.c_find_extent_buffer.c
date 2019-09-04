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
typedef  int u64 ;
struct extent_buffer {int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  bflags; int /*<<< orphan*/  refs; } ;
struct btrfs_fs_info {int /*<<< orphan*/  buffer_radix; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_STALE ; 
 int PAGE_SHIFT ; 
 scalar_t__ atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_extent_buffer_accessed (struct extent_buffer*,int /*<<< orphan*/ *) ; 
 struct extent_buffer* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct extent_buffer *find_extent_buffer(struct btrfs_fs_info *fs_info,
					 u64 start)
{
	struct extent_buffer *eb;

	rcu_read_lock();
	eb = radix_tree_lookup(&fs_info->buffer_radix,
			       start >> PAGE_SHIFT);
	if (eb && atomic_inc_not_zero(&eb->refs)) {
		rcu_read_unlock();
		/*
		 * Lock our eb's refs_lock to avoid races with
		 * free_extent_buffer. When we get our eb it might be flagged
		 * with EXTENT_BUFFER_STALE and another task running
		 * free_extent_buffer might have seen that flag set,
		 * eb->refs == 2, that the buffer isn't under IO (dirty and
		 * writeback flags not set) and it's still in the tree (flag
		 * EXTENT_BUFFER_TREE_REF set), therefore being in the process
		 * of decrementing the extent buffer's reference count twice.
		 * So here we could race and increment the eb's reference count,
		 * clear its stale flag, mark it as dirty and drop our reference
		 * before the other task finishes executing free_extent_buffer,
		 * which would later result in an attempt to free an extent
		 * buffer that is dirty.
		 */
		if (test_bit(EXTENT_BUFFER_STALE, &eb->bflags)) {
			spin_lock(&eb->refs_lock);
			spin_unlock(&eb->refs_lock);
		}
		mark_extent_buffer_accessed(eb, NULL);
		return eb;
	}
	rcu_read_unlock();

	return NULL;
}