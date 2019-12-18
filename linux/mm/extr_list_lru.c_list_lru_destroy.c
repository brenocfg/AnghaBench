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
struct list_lru {int shrinker_id; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_unregister (struct list_lru*) ; 
 int /*<<< orphan*/  memcg_destroy_list_lru (struct list_lru*) ; 
 int /*<<< orphan*/  memcg_get_cache_ids () ; 
 int /*<<< orphan*/  memcg_put_cache_ids () ; 

void list_lru_destroy(struct list_lru *lru)
{
	/* Already destroyed or not yet initialized? */
	if (!lru->node)
		return;

	memcg_get_cache_ids();

	list_lru_unregister(lru);

	memcg_destroy_list_lru(lru);
	kfree(lru->node);
	lru->node = NULL;

#ifdef CONFIG_MEMCG_KMEM
	lru->shrinker_id = -1;
#endif
	memcg_put_cache_ids();
}