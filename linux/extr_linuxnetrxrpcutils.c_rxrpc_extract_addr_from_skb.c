#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_15__ {TYPE_5__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_12__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_13__ {TYPE_3__ sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_16__ {TYPE_6__ sin; TYPE_4__ sin6; } ;
struct sockaddr_rxrpc {int transport_len; TYPE_7__ transport; void* transport_type; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_10__ {int /*<<< orphan*/  family; } ;
struct TYPE_11__ {TYPE_1__ transport; } ;
struct rxrpc_local {TYPE_2__ srx; } ;
struct TYPE_18__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_17__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EAFNOSUPPORT ; 
#define  ETH_P_IP 128 
 void* SOCK_DGRAM ; 
 int /*<<< orphan*/  htonl (int) ; 
 TYPE_9__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_rxrpc*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int) ; 
 TYPE_8__* udp_hdr (struct sk_buff*) ; 

int rxrpc_extract_addr_from_skb(struct rxrpc_local *local,
				struct sockaddr_rxrpc *srx,
				struct sk_buff *skb)
{
	memset(srx, 0, sizeof(*srx));

	switch (ntohs(skb->protocol)) {
	case ETH_P_IP:
		if (local->srx.transport.family == AF_INET6) {
			srx->transport_type = SOCK_DGRAM;
			srx->transport_len = sizeof(srx->transport.sin6);
			srx->transport.sin6.sin6_family = AF_INET6;
			srx->transport.sin6.sin6_port = udp_hdr(skb)->source;
			srx->transport.sin6.sin6_addr.s6_addr32[2] = htonl(0xffff);
			srx->transport.sin6.sin6_addr.s6_addr32[3] = ip_hdr(skb)->saddr;
		} else {
			srx->transport_type = SOCK_DGRAM;
			srx->transport_len = sizeof(srx->transport.sin);
			srx->transport.sin.sin_family = AF_INET;
			srx->transport.sin.sin_port = udp_hdr(skb)->source;
			srx->transport.sin.sin_addr.s_addr = ip_hdr(skb)->saddr;
		}
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