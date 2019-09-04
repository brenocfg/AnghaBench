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
struct urb {int /*<<< orphan*/  status; struct mt7601u_tx_queue* context; } ;
struct sk_buff {int dummy; } ;
struct mt7601u_tx_queue {size_t start; int used; int entries; TYPE_1__* e; struct mt7601u_dev* dev; } ;
struct mt7601u_dev {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  tx_skb_done; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct sk_buff* skb; struct urb* urb; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt7601u_urb_has_error (struct urb*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mt_tx_dma_done (struct mt7601u_dev*,struct sk_buff*) ; 

__attribute__((used)) static void mt7601u_complete_tx(struct urb *urb)
{
	struct mt7601u_tx_queue *q = urb->context;
	struct mt7601u_dev *dev = q->dev;
	struct sk_buff *skb;
	unsigned long flags;

	spin_lock_irqsave(&dev->tx_lock, flags);

	if (mt7601u_urb_has_error(urb))
		dev_err(dev->dev, "Error: TX urb failed:%d\n", urb->status);
	if (WARN_ONCE(q->e[q->start].urb != urb, "TX urb mismatch"))
		goto out;

	skb = q->e[q->start].skb;
	trace_mt_tx_dma_done(dev, skb);

	__skb_queue_tail(&dev->tx_skb_done, skb);
	tasklet_schedule(&dev->tx_tasklet);

	if (q->used == q->entries - q->entries / 8)
		ieee80211_wake_queue(dev->hw, skb_get_queue_mapping(skb));

	q->start = (q->start + 1) % q->entries;
	q->used--;
out:
	spin_unlock_irqrestore(&dev->tx_lock, flags);
}