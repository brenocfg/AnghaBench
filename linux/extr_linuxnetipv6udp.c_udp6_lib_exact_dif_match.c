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
struct net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool udp6_lib_exact_dif_match(struct net *net, struct sk_buff *skb)
{
#if defined(CONFIG_NET_L3_MASTER_DEV)
	if (!net->ipv4.sysctl_udp_l3mdev_accept &&
	    skb && ipv6_l3mdev_skb(IP6CB(skb)->flags))
		return true;
#endif
	return false;
}