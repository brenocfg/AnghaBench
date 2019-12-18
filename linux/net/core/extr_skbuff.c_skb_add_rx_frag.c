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
struct sk_buff {int len; int data_len; unsigned int truesize; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,int,int) ; 

void skb_add_rx_frag(struct sk_buff *skb, int i, struct page *page, int off,
		     int size, unsigned int truesize)
{
	skb_fill_page_desc(skb, i, page, off, size);
	skb->len += size;
	skb->data_len += size;
	skb->truesize += truesize;
}