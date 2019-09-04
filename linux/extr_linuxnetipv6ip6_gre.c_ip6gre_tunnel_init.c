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
struct net_device {int /*<<< orphan*/ * header_ops; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; scalar_t__ collect_md; } ;
struct ip6_tnl {TYPE_1__ parms; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6gre_header_ops ; 
 int ip6gre_tunnel_init_common (struct net_device*) ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ip6gre_tunnel_init(struct net_device *dev)
{
	struct ip6_tnl *tunnel;
	int ret;

	ret = ip6gre_tunnel_init_common(dev);
	if (ret)
		return ret;

	tunnel = netdev_priv(dev);

	if (tunnel->parms.collect_md)
		return 0;

	memcpy(dev->dev_addr, &tunnel->parms.laddr, sizeof(struct in6_addr));
	memcpy(dev->broadcast, &tunnel->parms.raddr, sizeof(struct in6_addr));

	if (ipv6_addr_any(&tunnel->parms.raddr))
		dev->header_ops = &ip6gre_header_ops;

	return 0;
}