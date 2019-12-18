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
typedef  scalar_t__ u_int8_t ;
struct xt_pkttype_info {scalar_t__ pkttype; int invert; } ;
struct xt_action_param {struct xt_pkttype_info* matchinfo; } ;
struct sk_buff {scalar_t__ pkt_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PACKET_MULTICAST ; 
 TYPE_1__* ip_hdr (struct sk_buff const*) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ xt_family (struct xt_action_param*) ; 

__attribute__((used)) static bool
pkttype_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_pkttype_info *info = par->matchinfo;
	u_int8_t type;

	if (skb->pkt_type != PACKET_LOOPBACK)
		type = skb->pkt_type;
	else if (xt_family(par) == NFPROTO_IPV4 &&
	    ipv4_is_multicast(ip_hdr(skb)->daddr))
		type = PACKET_MULTICAST;
	else if (xt_family(par) == NFPROTO_IPV6)
		type = PACKET_MULTICAST;
	else
		type = PACKET_BROADCAST;

	return (type == info->pkttype) ^ info->invert;
}