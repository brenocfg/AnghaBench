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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ tail; scalar_t__ end; scalar_t__ cb; } ;
struct mt76_queue {struct sk_buff* rx_head; int /*<<< orphan*/  buf_offset; int /*<<< orphan*/  buf_size; } ;
struct mt76_dev {struct mt76_queue* q_rx; TYPE_1__* drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rx_skb ) (struct mt76_dev*,int,struct sk_buff*) ;} ;

/* Variables and functions */
 size_t MT_RXQ_MCU ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* build_skb (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_add_fragment (struct mt76_dev*,struct mt76_queue*,unsigned char*,int,int) ; 
 unsigned char* mt76_dma_dequeue (struct mt76_dev*,struct mt76_queue*,int,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mt76_dma_rx_fill (struct mt76_dev*,struct mt76_queue*,int) ; 
 int /*<<< orphan*/  skb_free_frag (unsigned char*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,int,struct sk_buff*) ; 

__attribute__((used)) static int
mt76_dma_rx_process(struct mt76_dev *dev, struct mt76_queue *q, int budget)
{
	struct sk_buff *skb;
	unsigned char *data;
	int len;
	int done = 0;
	bool more;

	while (done < budget) {
		u32 info;

		data = mt76_dma_dequeue(dev, q, false, &len, &info, &more);
		if (!data)
			break;

		if (q->rx_head) {
			mt76_add_fragment(dev, q, data, len, more);
			continue;
		}

		skb = build_skb(data, q->buf_size);
		if (!skb) {
			skb_free_frag(data);
			continue;
		}

		skb_reserve(skb, q->buf_offset);
		if (skb->tail + len > skb->end) {
			dev_kfree_skb(skb);
			continue;
		}

		if (q == &dev->q_rx[MT_RXQ_MCU]) {
			u32 *rxfce = (u32 *) skb->cb;
			*rxfce = info;
		}

		__skb_put(skb, len);
		done++;

		if (more) {
			q->rx_head = skb;
			continue;
		}

		dev->drv->rx_skb(dev, q - dev->q_rx, skb);
	}

	mt76_dma_rx_fill(dev, q, true);
	return done;
}