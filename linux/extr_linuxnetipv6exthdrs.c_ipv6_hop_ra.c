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
struct TYPE_2__ {int /*<<< orphan*/  ra; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6SKB_ROUTERALERT ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,unsigned char const) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static bool ipv6_hop_ra(struct sk_buff *skb, int optoff)
{
	const unsigned char *nh = skb_network_header(skb);

	if (nh[optoff + 1] == 2) {
		IP6CB(skb)->flags |= IP6SKB_ROUTERALERT;
		memcpy(&IP6CB(skb)->ra, nh + optoff + 2, sizeof(IP6CB(skb)->ra));
		return true;
	}
	net_dbg_ratelimited("ipv6_hop_ra: wrong RA length %d\n",
			    nh[optoff + 1]);
	kfree_skb(skb);
	return false;
}