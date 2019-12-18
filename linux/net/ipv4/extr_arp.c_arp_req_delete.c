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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct TYPE_3__ {struct net_device* dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct arpreq {int arp_flags; int /*<<< orphan*/  arp_pa; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ATF_PUBL ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RTO_ONLINK ; 
 int arp_invalidate (struct net_device*,int /*<<< orphan*/ ) ; 
 int arp_req_delete_public (struct net*,struct arpreq*,struct net_device*) ; 
 struct rtable* ip_route_output (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 

__attribute__((used)) static int arp_req_delete(struct net *net, struct arpreq *r,
			  struct net_device *dev)
{
	__be32 ip;

	if (r->arp_flags & ATF_PUBL)
		return arp_req_delete_public(net, r, dev);

	ip = ((struct sockaddr_in *)&r->arp_pa)->sin_addr.s_addr;
	if (!dev) {
		struct rtable *rt = ip_route_output(net, ip, 0, RTO_ONLINK, 0);
		if (IS_ERR(rt))
			return PTR_ERR(rt);
		dev = rt->dst.dev;
		ip_rt_put(rt);
		if (!dev)
			return -EINVAL;
	}
	return arp_invalidate(dev, ip);
}