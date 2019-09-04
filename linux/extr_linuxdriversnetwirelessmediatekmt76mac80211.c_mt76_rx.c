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
struct sk_buff {int dummy; } ;
struct mt76_dev {int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  state; } ;
typedef  enum mt76_rxq_id { ____Placeholder_mt76_rxq_id } mt76_rxq_id ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mt76_rx(struct mt76_dev *dev, enum mt76_rxq_id q, struct sk_buff *skb)
{
	if (!test_bit(MT76_STATE_RUNNING, &dev->state)) {
		dev_kfree_skb(skb);
		return;
	}

	__skb_queue_tail(&dev->rx_skb[q], skb);
}