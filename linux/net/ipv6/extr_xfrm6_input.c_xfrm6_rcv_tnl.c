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
struct ip6_tnl {int dummy; } ;
struct TYPE_2__ {size_t nhoff; } ;

/* Variables and functions */
 TYPE_1__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 
 int xfrm6_rcv_spi (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip6_tnl*) ; 

int xfrm6_rcv_tnl(struct sk_buff *skb, struct ip6_tnl *t)
{
	return xfrm6_rcv_spi(skb, skb_network_header(skb)[IP6CB(skb)->nhoff],
			     0, t);
}