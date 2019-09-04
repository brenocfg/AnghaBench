#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rxrpc_sock {int /*<<< orphan*/  sk; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {TYPE_2__ sin_addr; } ;
struct TYPE_9__ {int family; TYPE_3__ sin; } ;
struct TYPE_10__ {TYPE_4__ transport; } ;
struct rxrpc_peer {int if_mtu; TYPE_5__ srx; } ;
struct dst_entry {int dummy; } ;
struct rtable {struct dst_entry dst; } ;
struct net {int dummy; } ;
struct flowi4 {int dummy; } ;
struct TYPE_6__ {struct flowi4 ip4; } ;
struct flowi {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  fl ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct rtable* ip_route_output_ports (struct net*,struct flowi4*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 struct net* sock_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_assess_MTU_size(struct rxrpc_sock *rx,
				  struct rxrpc_peer *peer)
{
	struct net *net = sock_net(&rx->sk);
	struct dst_entry *dst;
	struct rtable *rt;
	struct flowi fl;
	struct flowi4 *fl4 = &fl.u.ip4;
#ifdef CONFIG_AF_RXRPC_IPV6
	struct flowi6 *fl6 = &fl.u.ip6;
#endif

	peer->if_mtu = 1500;

	memset(&fl, 0, sizeof(fl));
	switch (peer->srx.transport.family) {
	case AF_INET:
		rt = ip_route_output_ports(
			net, fl4, NULL,
			peer->srx.transport.sin.sin_addr.s_addr, 0,
			htons(7000), htons(7001), IPPROTO_UDP, 0, 0);
		if (IS_ERR(rt)) {
			_leave(" [route err %ld]", PTR_ERR(rt));
			return;
		}
		dst = &rt->dst;
		break;

#ifdef CONFIG_AF_RXRPC_IPV6
	case AF_INET6:
		fl6->flowi6_iif = LOOPBACK_IFINDEX;
		fl6->flowi6_scope = RT_SCOPE_UNIVERSE;
		fl6->flowi6_proto = IPPROTO_UDP;
		memcpy(&fl6->daddr, &peer->srx.transport.sin6.sin6_addr,
		       sizeof(struct in6_addr));
		fl6->fl6_dport = htons(7001);
		fl6->fl6_sport = htons(7000);
		dst = ip6_route_output(net, NULL, fl6);
		if (dst->error) {
			_leave(" [route err %d]", dst->error);
			return;
		}
		break;
#endif

	default:
		BUG();
	}

	peer->if_mtu = dst_mtu(dst);
	dst_release(dst);

	_leave(" [if_mtu %u]", peer->if_mtu);
}