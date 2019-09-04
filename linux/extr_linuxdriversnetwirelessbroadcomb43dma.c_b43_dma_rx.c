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
struct b43_dmaring {int tx; int nr_slots; int current_slot; struct b43_dma_ops* ops; } ;
struct b43_dma_ops {int (* get_current_rxslot ) (struct b43_dmaring*) ;int /*<<< orphan*/  (* set_current_rxslot ) (struct b43_dmaring*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  dma_rx (struct b43_dmaring*,int*) ; 
 int next_slot (struct b43_dmaring*,int) ; 
 int stub1 (struct b43_dmaring*) ; 
 int /*<<< orphan*/  stub2 (struct b43_dmaring*,int) ; 
 int /*<<< orphan*/  update_max_used_slots (struct b43_dmaring*,int) ; 
 int /*<<< orphan*/  wmb () ; 

void b43_dma_rx(struct b43_dmaring *ring)
{
	const struct b43_dma_ops *ops = ring->ops;
	int slot, current_slot;
	int used_slots = 0;

	B43_WARN_ON(ring->tx);
	current_slot = ops->get_current_rxslot(ring);
	B43_WARN_ON(!(current_slot >= 0 && current_slot < ring->nr_slots));

	slot = ring->current_slot;
	for (; slot != current_slot; slot = next_slot(ring, slot)) {
		dma_rx(ring, &slot);
		update_max_used_slots(ring, ++used_slots);
	}
	wmb();
	ops->set_current_rxslot(ring, slot);
	ring->current_slot = slot;
}