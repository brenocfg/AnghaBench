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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct qdio_buffer_element {scalar_t__ addr; } ;
struct page {int dummy; } ;
struct TYPE_2__ {unsigned int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (struct page*) ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,unsigned int,struct page*,int,int,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 
 struct page* virt_to_page (scalar_t__) ; 

__attribute__((used)) static void qeth_create_skb_frag(struct qdio_buffer_element *element,
				 struct sk_buff *skb, int offset, int data_len)
{
	struct page *page = virt_to_page(element->addr);
	unsigned int next_frag;

	/* first fill the linear space */
	if (!skb->len) {
		unsigned int linear = min(data_len, skb_tailroom(skb));

		skb_put_data(skb, element->addr + offset, linear);
		data_len -= linear;
		if (!data_len)
			return;
		offset += linear;
		/* fall through to add page frag for remaining data */
	}

	next_frag = skb_shinfo(skb)->nr_frags;
	get_page(page);
	skb_add_rx_frag(skb, next_frag, page, offset, data_len, data_len);
}