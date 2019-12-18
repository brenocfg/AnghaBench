#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_11__ {TYPE_3__ sin6; TYPE_2__ sin; } ;
struct sockaddr_rxrpc {int transport_len; TYPE_4__ transport; void* transport_type; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_14__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_13__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_12__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EAFNOSUPPORT ; 
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 void* SOCK_DGRAM ; 
 TYPE_7__* ip_hdr (struct sk_buff*) ; 
 TYPE_6__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_rxrpc*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int) ; 
 TYPE_5__* udp_hdr (struct sk_buff*) ; 

int rxrpc_extract_addr_from_skb(struct sockaddr_rxrpc *srx, struct sk_buff *skb)
{
	memset(srx, 0, sizeof(*srx));

	switch (ntohs(skb->protocol)) {
	case ETH_P_IP:
		srx->transport_type = SOCK_DGRAM;
		srx->transport_len = sizeof(srx->transport.sin);
		srx->transport.sin.sin_family = AF_INET;
		srx->transport.sin.sin_port = udp_hdr(skb)->source;
		srx->transport.sin.sin_addr.s_addr = ip_hdr(skb)->saddr;
		return 0;

#ifdef CONFIG_AF_RXRPC_IPV6
	case ETH_P_IPV6:
		srx->transport_type = SOCK_DGRAM;
		srx->transport_len = sizeof(srx->transport.sin6);
		srx->transport.sin6.sin6_family = AF_INET6;
		srx->transport.sin6.sin6_port = udp_hdr(skb)->source;
		srx->transport.sin6.sin6_addr = ipv6_hdr(skb)->saddr;
		return 0;
#endif

	default:
		pr_warn_ratelimited("AF_RXRPC: Unknown eth protocol %u\n",
				    ntohs(skb->protocol));
		return -EAFNOSUPPORT;
	}
}