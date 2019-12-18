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
struct TYPE_3__ {struct net_device* dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct net_device {scalar_t__ mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  flags; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; scalar_t__ daddr; } ;
struct TYPE_4__ {scalar_t__ link; struct iphdr iph; } ;
struct ip_tunnel {int hlen; TYPE_2__ parms; int /*<<< orphan*/  net; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 scalar_t__ IPV6_MIN_MTU ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 struct rtable* ip_route_output_ports (int /*<<< orphan*/ ,struct flowi4*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_l3_master (struct net_device*) ; 

__attribute__((used)) static void ipip6_tunnel_bind_dev(struct net_device *dev)
{
	struct net_device *tdev = NULL;
	struct ip_tunnel *tunnel;
	const struct iphdr *iph;
	struct flowi4 fl4;

	tunnel = netdev_priv(dev);
	iph = &tunnel->parms.iph;

	if (iph->daddr) {
		struct rtable *rt = ip_route_output_ports(tunnel->net, &fl4,
							  NULL,
							  iph->daddr, iph->saddr,
							  0, 0,
							  IPPROTO_IPV6,
							  RT_TOS(iph->tos),
							  tunnel->parms.link);

		if (!IS_ERR(rt)) {
			tdev = rt->dst.dev;
			ip_rt_put(rt);
		}
		dev->flags |= IFF_POINTOPOINT;
	}

	if (!tdev && tunnel->parms.link)
		tdev = __dev_get_by_index(tunnel->net, tunnel->parms.link);

	if (tdev && !netif_is_l3_master(tdev)) {
		int t_hlen = tunnel->hlen + sizeof(struct iphdr);

		dev->hard_header_len = tdev->hard_header_len + sizeof(struct iphdr);
		dev->mtu = tdev->mtu - t_hlen;
		if (dev->mtu < IPV6_MIN_MTU)
			dev->mtu = IPV6_MIN_MTU;
	}
}