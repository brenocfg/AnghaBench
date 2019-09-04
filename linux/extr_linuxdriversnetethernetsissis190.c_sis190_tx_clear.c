#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct sis190_private {scalar_t__ dirty_tx; scalar_t__ cur_tx; TYPE_2__* dev; struct sk_buff** Tx_skbuff; scalar_t__ TxDescRing; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 unsigned int NUM_TX_DESC ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sis190_unmap_tx_skb (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void sis190_tx_clear(struct sis190_private *tp)
{
	unsigned int i;

	for (i = 0; i < NUM_TX_DESC; i++) {
		struct sk_buff *skb = tp->Tx_skbuff[i];

		if (!skb)
			continue;

		sis190_unmap_tx_skb(tp->pci_dev, skb, tp->TxDescRing + i);
		tp->Tx_skbuff[i] = NULL;
		dev_kfree_skb(skb);

		tp->dev->stats.tx_dropped++;
	}
	tp->cur_tx = tp->dirty_tx = 0;
}