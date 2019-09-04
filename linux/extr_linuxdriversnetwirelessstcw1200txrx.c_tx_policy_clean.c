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
struct TYPE_2__ {scalar_t__ usage_count; } ;
struct tx_policy_cache_entry {TYPE_1__ policy; int /*<<< orphan*/  link; } ;
struct tx_policy_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  free; struct tx_policy_cache_entry* cache; } ;
struct cw1200_common {struct tx_policy_cache tx_policy_cache; } ;

/* Variables and functions */
 int TX_POLICY_CACHE_SIZE ; 
 scalar_t__ WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  cw1200_tx_queues_lock (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_tx_queues_unlock (struct cw1200_common*) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void tx_policy_clean(struct cw1200_common *priv)
{
	int idx, locked;
	struct tx_policy_cache *cache = &priv->tx_policy_cache;
	struct tx_policy_cache_entry *entry;

	cw1200_tx_queues_lock(priv);
	spin_lock_bh(&cache->lock);
	locked = list_empty(&cache->free);

	for (idx = 0; idx < TX_POLICY_CACHE_SIZE; idx++) {
		entry = &cache->cache[idx];
		/* Policy usage count should be 0 at this time as all queues
		   should be empty
		 */
		if (WARN_ON(entry->policy.usage_count)) {
			entry->policy.usage_count = 0;
			list_move(&entry->link, &cache->free);
		}
		memset(&entry->policy, 0, sizeof(entry->policy));
	}
	if (locked)
		cw1200_tx_queues_unlock(priv);

	cw1200_tx_queues_unlock(priv);
	spin_unlock_bh(&cache->lock);
}