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
struct buffer_head {unsigned long b_state; int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 unsigned long EXT4_MAP_FLAGS ; 
 unsigned long READ_ONCE (unsigned long) ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ext4_update_bh_state(struct buffer_head *bh, unsigned long flags)
{
	unsigned long old_state;
	unsigned long new_state;

	flags &= EXT4_MAP_FLAGS;

	/* Dummy buffer_head? Set non-atomically. */
	if (!bh->b_page) {
		bh->b_state = (bh->b_state & ~EXT4_MAP_FLAGS) | flags;
		return;
	}
	/*
	 * Someone else may be modifying b_state. Be careful! This is ugly but
	 * once we get rid of using bh as a container for mapping information
	 * to pass to / from get_block functions, this can go away.
	 */
	do {
		old_state = READ_ONCE(bh->b_state);
		new_state = (old_state & ~EXT4_MAP_FLAGS) | flags;
	} while (unlikely(
		 cmpxchg(&bh->b_state, old_state, new_state) != old_state));
}