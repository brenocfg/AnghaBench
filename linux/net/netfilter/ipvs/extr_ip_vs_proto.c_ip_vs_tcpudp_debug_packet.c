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
struct ip_vs_protocol {int dummy; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/  ip_vs_tcpudp_debug_packet_v4 (struct ip_vs_protocol*,struct sk_buff const*,int,char const*) ; 
 int /*<<< orphan*/  ip_vs_tcpudp_debug_packet_v6 (struct ip_vs_protocol*,struct sk_buff const*,int,char const*) ; 

void
ip_vs_tcpudp_debug_packet(int af, struct ip_vs_protocol *pp,
			  const struct sk_buff *skb,
			  int offset,
			  const char *msg)
{
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6)
		ip_vs_tcpudp_debug_packet_v6(pp, skb, offset, msg);
	else
#endif
		ip_vs_tcpudp_debug_packet_v4(pp, skb, offset, msg);
}