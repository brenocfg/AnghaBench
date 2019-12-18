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
struct module {int dummy; } ;

/* Variables and functions */
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  snd_cards_lock ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_slot_from_bitmask(int mask, int (*check)(struct module *, int),
				 struct module *module)
{
	int slot;

	for (slot = 0; slot < SNDRV_CARDS; slot++) {
		if (slot < 32 && !(mask & (1U << slot)))
			continue;
		if (!test_bit(slot, snd_cards_lock)) {
			if (check(module, slot))
				return slot; /* found */
		}
	}
	return mask; /* unchanged */
}