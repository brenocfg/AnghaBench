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
struct swap_info_struct {unsigned int max; int /*<<< orphan*/ * swap_map; } ;

/* Variables and functions */
 unsigned int LATENCY_LIMIT ; 
 unsigned char READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ SWAP_MAP_BAD ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ frontswap_test (struct swap_info_struct*,unsigned int) ; 
 scalar_t__ swap_count (unsigned char) ; 

__attribute__((used)) static unsigned int find_next_to_unuse(struct swap_info_struct *si,
					unsigned int prev, bool frontswap)
{
	unsigned int i;
	unsigned char count;

	/*
	 * No need for swap_lock here: we're just looking
	 * for whether an entry is in use, not modifying it; false
	 * hits are okay, and sys_swapoff() has already prevented new
	 * allocations from this area (while holding swap_lock).
	 */
	for (i = prev + 1; i < si->max; i++) {
		count = READ_ONCE(si->swap_map[i]);
		if (count && swap_count(count) != SWAP_MAP_BAD)
			if (!frontswap || frontswap_test(si, i))
				break;
		if ((i % LATENCY_LIMIT) == 0)
			cond_resched();
	}

	if (i == si->max)
		i = 0;

	return i;
}