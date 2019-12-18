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
struct udphdr {int dummy; } ;
struct rxrpc_wire_header {int dummy; } ;
struct rxrpc_sock {int dummy; } ;
struct TYPE_3__ {int family; } ;
struct TYPE_4__ {int transport_type; TYPE_1__ transport; } ;
struct rxrpc_peer {unsigned long hash_key; int mtu; int if_mtu; int hdrsize; int maxdata; TYPE_2__ srx; int /*<<< orphan*/  rtt_last_req; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
 int /*<<< orphan*/  BUG () ; 
#define  SOCK_DGRAM 128 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  rxrpc_assess_MTU_size (struct rxrpc_sock*,struct rxrpc_peer*) ; 

__attribute__((used)) static void rxrpc_init_peer(struct rxrpc_sock *rx, struct rxrpc_peer *peer,
			    unsigned long hash_key)
{
	peer->hash_key = hash_key;
	rxrpc_assess_MTU_size(rx, peer);
	peer->mtu = peer->if_mtu;
	peer->rtt_last_req = ktime_get_real();

	switch (peer->srx.transport.family) {
	case AF_INET:
		peer->hdrsize = sizeof(struct iphdr);
		break;
#ifdef CONFIG_AF_RXRPC_IPV6
	case AF_INET6:
		peer->hdrsize = sizeof(struct ipv6hdr);
		break;
#endif
	default:
		BUG();
	}

	switch (peer->srx.transport_type) {
	case SOCK_DGRAM:
		peer->hdrsize += sizeof(struct udphdr);
		break;
	default:
		BUG();
	}

	peer->hdrsize += sizeof(struct rxrpc_wire_header);
	peer->maxdata = peer->mtu - peer->hdrsize;
}