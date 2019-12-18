#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netns_ipvs {int /*<<< orphan*/  net; } ;
struct dst_entry {TYPE_1__* dev; } ;
struct TYPE_4__ {int rt_flags; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int IFF_LOOPBACK ; 
 unsigned int NF_INET_LOCAL_IN ; 
 int RTCF_LOCAL ; 
 int /*<<< orphan*/  RTN_LOCAL ; 
 scalar_t__ ip6_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ ip_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 TYPE_2__* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  sysctl_snat_reroute (struct netns_ipvs*) ; 

__attribute__((used)) static int ip_vs_route_me_harder(struct netns_ipvs *ipvs, int af,
				 struct sk_buff *skb, unsigned int hooknum)
{
	if (!sysctl_snat_reroute(ipvs))
		return 0;
	/* Reroute replies only to remote clients (FORWARD and LOCAL_OUT) */
	if (NF_INET_LOCAL_IN == hooknum)
		return 0;
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6) {
		struct dst_entry *dst = skb_dst(skb);

		if (dst->dev && !(dst->dev->flags & IFF_LOOPBACK) &&
		    ip6_route_me_harder(ipvs->net, skb) != 0)
			return 1;
	} else
#endif
		if (!(skb_rtable(skb)->rt_flags & RTCF_LOCAL) &&
		    ip_route_me_harder(ipvs->net, skb, RTN_LOCAL) != 0)
			return 1;

	return 0;
}