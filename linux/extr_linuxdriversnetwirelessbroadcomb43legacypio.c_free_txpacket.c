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
struct b43legacy_pioqueue {int /*<<< orphan*/  nr_txfree; int /*<<< orphan*/  txfree; } ;
struct b43legacy_pio_txpacket {int /*<<< orphan*/  list; scalar_t__ skb; struct b43legacy_pioqueue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (scalar_t__) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_txpacket(struct b43legacy_pio_txpacket *packet,
			  int irq_context)
{
	struct b43legacy_pioqueue *queue = packet->queue;

	if (packet->skb) {
		if (irq_context)
			dev_kfree_skb_irq(packet->skb);
		else
			dev_kfree_skb(packet->skb);
	}
	list_move(&packet->list, &queue->txfree);
	queue->nr_txfree++;
}