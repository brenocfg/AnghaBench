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
struct skb_frag_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_2__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 scalar_t__ qeth_get_elements_for_range (scalar_t__,scalar_t__) ; 
 scalar_t__ skb_frag_address (struct skb_frag_struct*) ; 
 scalar_t__ skb_frag_size (struct skb_frag_struct*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

int qeth_get_elements_for_frags(struct sk_buff *skb)
{
	int cnt, elements = 0;

	for (cnt = 0; cnt < skb_shinfo(skb)->nr_frags; cnt++) {
		struct skb_frag_struct *frag = &skb_shinfo(skb)->frags[cnt];

		elements += qeth_get_elements_for_range(
			(addr_t)skb_frag_address(frag),
			(addr_t)skb_frag_address(frag) + skb_frag_size(frag));
	}
	return elements;
}