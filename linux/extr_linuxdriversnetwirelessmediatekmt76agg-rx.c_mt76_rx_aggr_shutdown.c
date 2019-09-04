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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct mt76_rx_tid {int size; int stopped; int /*<<< orphan*/  lock; scalar_t__ nframes; struct sk_buff** reorder_buf; int /*<<< orphan*/  reorder_work; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76_rx_aggr_shutdown(struct mt76_dev *dev, struct mt76_rx_tid *tid)
{
	u8 size = tid->size;
	int i;

	cancel_delayed_work(&tid->reorder_work);

	spin_lock_bh(&tid->lock);

	tid->stopped = true;
	for (i = 0; tid->nframes && i < size; i++) {
		struct sk_buff *skb = tid->reorder_buf[i];

		if (!skb)
			continue;

		tid->nframes--;
		dev_kfree_skb(skb);
	}

	spin_unlock_bh(&tid->lock);
}