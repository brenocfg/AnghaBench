#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* dev; } ;
struct rt6_info {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {int rt_flags; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int IFF_LOOPBACK ; 
 int IPV6_ADDR_LOOPBACK ; 
 int IP_VS_RT_MODE_LOCAL ; 
 int IP_VS_RT_MODE_NON_LOCAL ; 
 int IP_VS_RT_MODE_RDR ; 
 int RTCF_LOCAL ; 
 int __ip_vs_is_local_route6 (struct rt6_info*) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int ipv4_is_loopback (int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 
 TYPE_2__* skb_rtable (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool crosses_local_route_boundary(int skb_af, struct sk_buff *skb,
						int rt_mode,
						bool new_rt_is_local)
{
	bool rt_mode_allow_local = !!(rt_mode & IP_VS_RT_MODE_LOCAL);
	bool rt_mode_allow_non_local = !!(rt_mode & IP_VS_RT_MODE_NON_LOCAL);
	bool rt_mode_allow_redirect = !!(rt_mode & IP_VS_RT_MODE_RDR);
	bool source_is_loopback;
	bool old_rt_is_local;

#ifdef CONFIG_IP_VS_IPV6
	if (skb_af == AF_INET6) {
		int addr_type = ipv6_addr_type(&ipv6_hdr(skb)->saddr);

		source_is_loopback =
			(!skb->dev || skb->dev->flags & IFF_LOOPBACK) &&
			(addr_type & IPV6_ADDR_LOOPBACK);
		old_rt_is_local = __ip_vs_is_local_route6(
			(struct rt6_info *)skb_dst(skb));
	} else
#endif
	{
		source_is_loopback = ipv4_is_loopback(ip_hdr(skb)->saddr);
		old_rt_is_local = skb_rtable(skb)->rt_flags & RTCF_LOCAL;
	}

	if (unlikely(new_rt_is_local)) {
		if (!rt_mode_allow_local)
			return true;
		if (!rt_mode_allow_redirect && !old_rt_is_local)
			return true;
	} else {
		if (!rt_mode_allow_non_local)
			return true;
		if (source_is_loopback)
			return true;
	}
	return false;
}