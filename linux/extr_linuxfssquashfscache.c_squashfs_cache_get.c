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
struct super_block {int dummy; } ;
struct squashfs_cache_entry {scalar_t__ block; scalar_t__ refcount; int pending; scalar_t__ error; scalar_t__ length; int /*<<< orphan*/  wait_queue; scalar_t__ num_waiters; int /*<<< orphan*/  actor; int /*<<< orphan*/  next_index; } ;
struct squashfs_cache {int curr_blk; int entries; scalar_t__ unused; int next_blk; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; struct squashfs_cache_entry* entry; int /*<<< orphan*/  num_waiters; int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ squashfs_read_data (struct super_block*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

struct squashfs_cache_entry *squashfs_cache_get(struct super_block *sb,
	struct squashfs_cache *cache, u64 block, int length)
{
	int i, n;
	struct squashfs_cache_entry *entry;

	spin_lock(&cache->lock);

	while (1) {
		for (i = cache->curr_blk, n = 0; n < cache->entries; n++) {
			if (cache->entry[i].block == block) {
				cache->curr_blk = i;
				break;
			}
			i = (i + 1) % cache->entries;
		}

		if (n == cache->entries) {
			/*
			 * Block not in cache, if all cache entries are used
			 * go to sleep waiting for one to become available.
			 */
			if (cache->unused == 0) {
				cache->num_waiters++;
				spin_unlock(&cache->lock);
				wait_event(cache->wait_queue, cache->unused);
				spin_lock(&cache->lock);
				cache->num_waiters--;
				continue;
			}

			/*
			 * At least one unused cache entry.  A simple
			 * round-robin strategy is used to choose the entry to
			 * be evicted from the cache.
			 */
			i = cache->next_blk;
			for (n = 0; n < cache->entries; n++) {
				if (cache->entry[i].refcount == 0)
					break;
				i = (i + 1) % cache->entries;
			}

			cache->next_blk = (i + 1) % cache->entries;
			entry = &cache->entry[i];

			/*
			 * Initialise chosen cache entry, and fill it in from
			 * disk.
			 */
			cache->unused--;
			entry->block = block;
			entry->refcount = 1;
			entry->pending = 1;
			entry->num_waiters = 0;
			entry->error = 0;
			spin_unlock(&cache->lock);

			entry->length = squashfs_read_data(sb, block, length,
				&entry->next_index, entry->actor);

			spin_lock(&cache->lock);

			if (entry->length < 0)
				entry->error = entry->length;

			entry->pending = 0;

			/*
			 * While filling this entry one or more other processes
			 * have looked it up in the cache, and have slept
			 * waiting for it to become available.
			 */
			if (entry->num_waiters) {
				spin_unlock(&cache->lock);
				wake_up_all(&entry->wait_queue);
			} else
				spin_unlock(&cache->lock);

			goto out;
		}

		/*
		 * Block already in cache.  Increment refcount so it doesn't
		 * get reused until we're finished with it, if it was
		 * previously unused there's one less cache entry available
		 * for reuse.
		 */
		entry = &cache->entry[i];
		if (entry->refcount == 0)
			cache->unused--;
		entry->refcount++;

		/*
		 * If the entry is currently being filled in by another process
		 * go to sleep waiting for it to become available.
		 */
		if (entry->pending) {
			entry->num_waiters++;
			spin_unlock(&cache->lock);
			wait_event(entry->wait_queue, !entry->pending);
		} else
			spin_unlock(&cache->lock);

		goto out;
	}

out:
	TRACE("Got %s %d, start block %lld, refcount %d, error %d\n",
		cache->name, i, entry->block, entry->refcount, entry->error);

	if (entry->error)
		ERROR("Unable to read %s cache entry [%llx]\n", cache->name,
							block);
	return entry;
}