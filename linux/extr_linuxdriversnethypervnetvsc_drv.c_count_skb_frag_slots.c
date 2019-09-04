#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {unsigned long page_offset; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_5__ {int nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PFN_UP (unsigned long) ; 
 unsigned long skb_frag_size (TYPE_1__*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int count_skb_frag_slots(struct sk_buff *skb)
{
	int i, frags = skb_shinfo(skb)->nr_frags;
	int pages = 0;

	for (i = 0; i < frags; i++) {
		skb_frag_t *frag = skb_shinfo(skb)->frags + i;
		unsigned long size = skb_frag_size(frag);
		unsigned long offset = frag->page_offset;

		/* Skip unused frames from start of page */
		offset &= ~PAGE_MASK;
		pages += PFN_UP(offset + size);
	}
	return pages;
}