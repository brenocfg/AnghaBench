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
struct tx_policy_cache {int /*<<< orphan*/  free; TYPE_1__* cache; int /*<<< orphan*/  used; int /*<<< orphan*/  lock; } ;
struct cw1200_common {struct tx_policy_cache tx_policy_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TX_POLICY_CACHE_SIZE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tx_policy_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void tx_policy_init(struct cw1200_common *priv)
{
	struct tx_policy_cache *cache = &priv->tx_policy_cache;
	int i;

	memset(cache, 0, sizeof(*cache));

	spin_lock_init(&cache->lock);
	INIT_LIST_HEAD(&cache->used);
	INIT_LIST_HEAD(&cache->free);

	for (i = 0; i < TX_POLICY_CACHE_SIZE; ++i)
		list_add(&cache->cache[i].link, &cache->free);
}