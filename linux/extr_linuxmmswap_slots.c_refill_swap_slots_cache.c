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
struct swap_slots_cache {int nr; int /*<<< orphan*/  slots; scalar_t__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_SLOTS_CACHE_SIZE ; 
 int get_swap_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ swap_slot_cache_active ; 
 int /*<<< orphan*/  use_swap_slot_cache ; 

__attribute__((used)) static int refill_swap_slots_cache(struct swap_slots_cache *cache)
{
	if (!use_swap_slot_cache || cache->nr)
		return 0;

	cache->cur = 0;
	if (swap_slot_cache_active)
		cache->nr = get_swap_pages(SWAP_SLOTS_CACHE_SIZE,
					   cache->slots, 1);

	return cache->nr;
}