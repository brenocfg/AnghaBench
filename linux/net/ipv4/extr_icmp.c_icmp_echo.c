#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  sysctl_icmp_echo_ignore_all; } ;
struct net {TYPE_1__ ipv4; } ;
struct icmphdr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_4__ icmph; } ;
struct icmp_bxm {int head_len; int /*<<< orphan*/  data_len; scalar_t__ offset; struct sk_buff* skb; TYPE_2__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_ECHOREPLY ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 TYPE_4__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  icmp_reply (struct icmp_bxm*,struct sk_buff*) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static bool icmp_echo(struct sk_buff *skb)
{
	struct net *net;

	net = dev_net(skb_dst(skb)->dev);
	if (!net->ipv4.sysctl_icmp_echo_ignore_all) {
		struct icmp_bxm icmp_param;

		icmp_param.data.icmph	   = *icmp_hdr(skb);
		icmp_param.data.icmph.type = ICMP_ECHOREPLY;
		icmp_param.skb		   = skb;
		icmp_param.offset	   = 0;
		icmp_param.data_len	   = skb->len;
		icmp_param.head_len	   = sizeof(struct icmphdr);
		icmp_reply(&icmp_param, skb);
	}
	/* should there be an ICMP stat for ignored echos? */
	return true;
}