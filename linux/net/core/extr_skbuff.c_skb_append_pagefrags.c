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
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ skb_can_coalesce (struct sk_buff*,int,struct page*,int) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,int,size_t) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

int skb_append_pagefrags(struct sk_buff *skb, struct page *page,
			 int offset, size_t size)
{
	int i = skb_shinfo(skb)->nr_frags;

	if (skb_can_coalesce(skb, i, page, offset)) {
		skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], size);
	} else if (i < MAX_SKB_FRAGS) {
		get_page(page);
		skb_fill_page_desc(skb, i, page, offset, size);
	} else {
		return -EMSGSIZE;
	}

	return 0;
}