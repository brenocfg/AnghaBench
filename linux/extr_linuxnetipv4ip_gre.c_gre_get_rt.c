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
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct rtable {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_3__ {TYPE_2__ ipv4; } ;
struct ip_tunnel_key {int /*<<< orphan*/  tos; TYPE_1__ u; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 struct rtable* ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct rtable *gre_get_rt(struct sk_buff *skb,
				 struct net_device *dev,
				 struct flowi4 *fl,
				 const struct ip_tunnel_key *key)
{
	struct net *net = dev_net(dev);

	memset(fl, 0, sizeof(*fl));
	fl->daddr = key->u.ipv4.dst;
	fl->saddr = key->u.ipv4.src;
	fl->flowi4_tos = RT_TOS(key->tos);
	fl->flowi4_mark = skb->mark;
	fl->flowi4_proto = IPPROTO_GRE;

	return ip_route_output_key(net, fl);
}