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
struct squashfs_cache_entry {scalar_t__ refcount; struct squashfs_cache* cache; } ;
struct squashfs_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_queue; scalar_t__ num_waiters; int /*<<< orphan*/  unused; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void squashfs_cache_put(struct squashfs_cache_entry *entry)
{
	struct squashfs_cache *cache = entry->cache;

	spin_lock(&cache->lock);
	entry->refcount--;
	if (entry->refcount == 0) {
		cache->unused++;
		/*
		 * If there's any processes waiting for a block to become
		 * available, wake one up.
		 */
		if (cache->num_waiters) {
			spin_unlock(&cache->lock);
			wake_up(&cache->wait_queue);
			return;
		}
	}
	spin_unlock(&cache->lock);
}