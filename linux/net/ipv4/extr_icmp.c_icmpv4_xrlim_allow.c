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
struct dst_entry {TYPE_2__* dev; } ;
struct rtable {struct dst_entry dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  sysctl_icmp_ratelimit; int /*<<< orphan*/  peers; } ;
struct net {TYPE_1__ ipv4; } ;
struct inet_peer {int dummy; } ;
struct flowi4 {int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 scalar_t__ icmpv4_mask_allow (struct net*,int,int) ; 
 struct inet_peer* inet_getpeer_v4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int inet_peer_xrlim_allow (struct inet_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_putpeer (struct inet_peer*) ; 
 int l3mdev_master_ifindex (TYPE_2__*) ; 

__attribute__((used)) static bool icmpv4_xrlim_allow(struct net *net, struct rtable *rt,
			       struct flowi4 *fl4, int type, int code)
{
	struct dst_entry *dst = &rt->dst;
	struct inet_peer *peer;
	bool rc = true;
	int vif;

	if (icmpv4_mask_allow(net, type, code))
		goto out;

	/* No rate limit on loopback */
	if (dst->dev && (dst->dev->flags&IFF_LOOPBACK))
		goto out;

	vif = l3mdev_master_ifindex(dst->dev);
	peer = inet_getpeer_v4(net->ipv4.peers, fl4->daddr, vif, 1);
	rc = inet_peer_xrlim_allow(peer, net->ipv4.sysctl_icmp_ratelimit);
	if (peer)
		inet_putpeer(peer);
out:
	return rc;
}