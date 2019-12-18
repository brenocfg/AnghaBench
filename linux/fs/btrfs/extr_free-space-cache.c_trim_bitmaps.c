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
struct btrfs_trim_range {int /*<<< orphan*/  list; scalar_t__ bytes; scalar_t__ start; } ;
struct btrfs_free_space_ctl {scalar_t__ free_space; int unit; int /*<<< orphan*/  cache_writeout_mutex; int /*<<< orphan*/  trimming_ranges; int /*<<< orphan*/  tree_lock; } ;
struct btrfs_free_space {scalar_t__ bytes; } ;
struct btrfs_block_group_cache {struct btrfs_free_space_ctl* free_space_ctl; } ;

/* Variables and functions */
 int BITS_PER_BITMAP ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  bitmap_clear_bits (struct btrfs_free_space_ctl*,struct btrfs_free_space*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int do_trimming (struct btrfs_block_group_cache*,scalar_t__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,struct btrfs_trim_range*) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ offset_to_bitmap (struct btrfs_free_space_ctl*,scalar_t__) ; 
 int search_bitmap (struct btrfs_free_space_ctl*,struct btrfs_free_space*,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct btrfs_free_space* tree_search_offset (struct btrfs_free_space_ctl*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trim_bitmaps(struct btrfs_block_group_cache *block_group,
			u64 *total_trimmed, u64 start, u64 end, u64 minlen)
{
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;
	struct btrfs_free_space *entry;
	int ret = 0;
	int ret2;
	u64 bytes;
	u64 offset = offset_to_bitmap(ctl, start);

	while (offset < end) {
		bool next_bitmap = false;
		struct btrfs_trim_range trim_entry;

		mutex_lock(&ctl->cache_writeout_mutex);
		spin_lock(&ctl->tree_lock);

		if (ctl->free_space < minlen) {
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_writeout_mutex);
			break;
		}

		entry = tree_search_offset(ctl, offset, 1, 0);
		if (!entry) {
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_writeout_mutex);
			next_bitmap = true;
			goto next;
		}

		bytes = minlen;
		ret2 = search_bitmap(ctl, entry, &start, &bytes, false);
		if (ret2 || start >= end) {
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_writeout_mutex);
			next_bitmap = true;
			goto next;
		}

		bytes = min(bytes, end - start);
		if (bytes < minlen) {
			spin_unlock(&ctl->tree_lock);
			mutex_unlock(&ctl->cache_writeout_mutex);
			goto next;
		}

		bitmap_clear_bits(ctl, entry, start, bytes);
		if (entry->bytes == 0)
			free_bitmap(ctl, entry);

		spin_unlock(&ctl->tree_lock);
		trim_entry.start = start;
		trim_entry.bytes = bytes;
		list_add_tail(&trim_entry.list, &ctl->trimming_ranges);
		mutex_unlock(&ctl->cache_writeout_mutex);

		ret = do_trimming(block_group, total_trimmed, start, bytes,
				  start, bytes, &trim_entry);
		if (ret)
			break;
next:
		if (next_bitmap) {
			offset += BITS_PER_BITMAP * ctl->unit;
		} else {
			start += bytes;
			if (start >= offset + BITS_PER_BITMAP * ctl->unit)
				offset += BITS_PER_BITMAP * ctl->unit;
		}

		if (fatal_signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}

		cond_resched();
	}

	return ret;
}