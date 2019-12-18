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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct iphdr {int ihl; } ;
struct icmphdr {scalar_t__ type; } ;
struct TYPE_2__ {int type; int code; } ;

/* Variables and functions */
 int ICMP_DEST_UNREACH ; 
 scalar_t__ ICMP_ECHOREPLY ; 
 int ICMP_FRAG_NEEDED ; 
 int ICMP_REDIRECT ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 TYPE_1__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_redirect (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_update_pmtu (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ping_err (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

int icmp_err(struct sk_buff *skb, u32 info)
{
	struct iphdr *iph = (struct iphdr *)skb->data;
	int offset = iph->ihl<<2;
	struct icmphdr *icmph = (struct icmphdr *)(skb->data + offset);
	int type = icmp_hdr(skb)->type;
	int code = icmp_hdr(skb)->code;
	struct net *net = dev_net(skb->dev);

	/*
	 * Use ping_err to handle all icmp errors except those
	 * triggered by ICMP_ECHOREPLY which sent from kernel.
	 */
	if (icmph->type != ICMP_ECHOREPLY) {
		ping_err(skb, offset, info);
		return 0;
	}

	if (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED)
		ipv4_update_pmtu(skb, net, info, 0, IPPROTO_ICMP);
	else if (type == ICMP_REDIRECT)
		ipv4_redirect(skb, net, 0, IPPROTO_ICMP);

	return 0;
}