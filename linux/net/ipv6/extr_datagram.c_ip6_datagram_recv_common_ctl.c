#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct msghdr {int dummy; } ;
struct TYPE_7__ {scalar_t__ rxinfo; } ;
struct TYPE_8__ {TYPE_1__ bits; } ;
struct ipv6_pinfo {TYPE_2__ rxopt; } ;
struct in6_pktinfo {scalar_t__ ipi6_ifindex; int /*<<< orphan*/  ipi6_addr; } ;
typedef  int /*<<< orphan*/  src_info ;
struct TYPE_12__ {scalar_t__ iif; } ;
struct TYPE_11__ {scalar_t__ ipi_ifindex; } ;
struct TYPE_10__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_9__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_6__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 TYPE_5__* PKTINFO_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_set_v4mapped (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct in6_pktinfo*) ; 

void ip6_datagram_recv_common_ctl(struct sock *sk, struct msghdr *msg,
				 struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	bool is_ipv6 = skb->protocol == htons(ETH_P_IPV6);

	if (np->rxopt.bits.rxinfo) {
		struct in6_pktinfo src_info;

		if (is_ipv6) {
			src_info.ipi6_ifindex = IP6CB(skb)->iif;
			src_info.ipi6_addr = ipv6_hdr(skb)->daddr;
		} else {
			src_info.ipi6_ifindex =
				PKTINFO_SKB_CB(skb)->ipi_ifindex;
			ipv6_addr_set_v4mapped(ip_hdr(skb)->daddr,
					       &src_info.ipi6_addr);
		}

		if (src_info.ipi6_ifindex >= 0)
			put_cmsg(msg, SOL_IPV6, IPV6_PKTINFO,
				 sizeof(src_info), &src_info);
	}
}