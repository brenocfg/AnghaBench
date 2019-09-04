#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rtable {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct ip_tunnel_info {TYPE_3__ key; } ;
struct flowi4 {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 struct rtable* gre_get_rt (struct sk_buff*,struct net_device*,struct flowi4*,TYPE_3__*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 struct ip_tunnel_info* skb_tunnel_info (struct sk_buff*) ; 

__attribute__((used)) static int gre_fill_metadata_dst(struct net_device *dev, struct sk_buff *skb)
{
	struct ip_tunnel_info *info = skb_tunnel_info(skb);
	struct rtable *rt;
	struct flowi4 fl4;

	if (ip_tunnel_info_af(info) != AF_INET)
		return -EINVAL;

	rt = gre_get_rt(skb, dev, &fl4, &info->key);
	if (IS_ERR(rt))
		return PTR_ERR(rt);

	ip_rt_put(rt);
	info->key.u.ipv4.src = fl4.saddr;
	return 0;
}