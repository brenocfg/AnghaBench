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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tp_dst; int /*<<< orphan*/  tp_src; } ;
struct ip_tunnel_info {TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_DPORT ; 
 int /*<<< orphan*/  NFTA_TUNNEL_KEY_SPORT ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_ports_dump(struct sk_buff *skb,
				 struct ip_tunnel_info *info)
{
	if (nla_put_be16(skb, NFTA_TUNNEL_KEY_SPORT, htons(info->key.tp_src)) < 0 ||
	    nla_put_be16(skb, NFTA_TUNNEL_KEY_DPORT, htons(info->key.tp_dst)) < 0)
		return -1;

	return 0;
}