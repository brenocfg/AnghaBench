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
struct b43legacy_dmaring {int stopped; int current_slot; int /*<<< orphan*/  used_slots; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 scalar_t__ free_slots (struct b43legacy_dmaring*) ; 
 int next_slot (struct b43legacy_dmaring*,int) ; 
 int /*<<< orphan*/  update_max_used_slots (struct b43legacy_dmaring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
int request_slot(struct b43legacy_dmaring *ring)
{
	int slot;

	B43legacy_WARN_ON(!ring->tx);
	B43legacy_WARN_ON(ring->stopped);
	B43legacy_WARN_ON(free_slots(ring) == 0);

	slot = next_slot(ring, ring->current_slot);
	ring->current_slot = slot;
	ring->used_slots++;

	update_max_used_slots(ring, ring->used_slots);

	return slot;
}