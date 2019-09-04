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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  pkt_type; } ;
struct ieee802154_local {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  skb_queue; } ;
struct ieee802154_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lqi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_RX_MSG ; 
 struct ieee802154_local* hw_to_local (struct ieee802154_hw*) ; 
 TYPE_1__* mac_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void
ieee802154_rx_irqsafe(struct ieee802154_hw *hw, struct sk_buff *skb, u8 lqi)
{
	struct ieee802154_local *local = hw_to_local(hw);

	mac_cb(skb)->lqi = lqi;
	skb->pkt_type = IEEE802154_RX_MSG;
	skb_queue_tail(&local->skb_queue, skb);
	tasklet_schedule(&local->tasklet);
}