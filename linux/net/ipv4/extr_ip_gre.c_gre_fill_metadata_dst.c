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
struct TYPE_3__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;
struct ip_tunnel_key {TYPE_2__ u; int /*<<< orphan*/  tos; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {struct ip_tunnel_key key; } ;
struct flowi4 {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct rtable* ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  ip_tunnel_init_flow (struct flowi4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_hash (struct sk_buff*) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gre_fill_metadata_dst(struct net_device *dev, struct sk_buff *skb)
{
	struct ip_tunnel_info *info = skb_tunnel_info(skb);
	const struct ip_tunnel_key *key;
	struct rtable *rt;
	struct flowi4 fl4;

	if (ip_tunnel_info_af(info) != AF_INET)
		return -EINVAL;

	key = &info->key;
	ip_tunnel_init_flow(&fl4, IPPROTO_GRE, key->u.ipv4.dst, key->u.ipv4.src,
			    tunnel_id_to_key32(key->tun_id), key->tos, 0,
			    skb->mark, skb_get_hash(skb));
	rt = ip_route_output_key(dev_net(dev), &fl4);
	if (IS_ERR(rt))
		return PTR_ERR(rt);

	ip_rt_put(rt);
	info->key.u.ipv4.src = fl4.saddr;
	return 0;
}