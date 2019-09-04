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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int illegal_highdma(struct net_device *dev, struct sk_buff *skb)
{
#ifdef CONFIG_HIGHMEM
	int i;

	if (!(dev->features & NETIF_F_HIGHDMA)) {
		for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			if (PageHighMem(skb_frag_page(frag)))
				return 1;
		}
	}
#endif
	return 0;
}