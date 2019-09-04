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
struct page {int dummy; } ;
struct mt76_queue {struct sk_buff* rx_head; int /*<<< orphan*/  buf_size; scalar_t__ buf_offset; } ;
struct mt76_dev {int q_rx; TYPE_1__* drv; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rx_skb ) (struct mt76_dev*,struct mt76_queue*,struct sk_buff*) ;} ;

/* Variables and functions */
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct mt76_queue*,struct sk_buff*) ; 
 struct page* virt_to_head_page (void*) ; 

__attribute__((used)) static void
mt76_add_fragment(struct mt76_dev *dev, struct mt76_queue *q, void *data,
		  int len, bool more)
{
	struct page *page = virt_to_head_page(data);
	int offset = data - page_address(page);
	struct sk_buff *skb = q->rx_head;

	offset += q->buf_offset;
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page, offset, len,
			q->buf_size);

	if (more)
		return;

	q->rx_head = NULL;
	dev->drv->rx_skb(dev, q - dev->q_rx, skb);
}