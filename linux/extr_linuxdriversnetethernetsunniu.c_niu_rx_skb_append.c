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
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,struct page*,scalar_t__,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void niu_rx_skb_append(struct sk_buff *skb, struct page *page,
			      u32 offset, u32 size, u32 truesize)
{
	skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags, page, offset, size);

	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
}