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
struct TYPE_2__ {int /*<<< orphan*/  sysctl_ip_default_ttl; } ;
struct net {TYPE_1__ ipv4; } ;
struct iphdr {int version; int ihl; void* daddr; void* saddr; scalar_t__ check; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ttl; int /*<<< orphan*/  frag_off; scalar_t__ id; scalar_t__ tos; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct iphdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static struct iphdr *
synproxy_build_ip(struct net *net, struct sk_buff *skb, __be32 saddr,
		  __be32 daddr)
{
	struct iphdr *iph;

	skb_reset_network_header(skb);
	iph = skb_put(skb, sizeof(*iph));
	iph->version	= 4;
	iph->ihl	= sizeof(*iph) / 4;
	iph->tos	= 0;
	iph->id		= 0;
	iph->frag_off	= htons(IP_DF);
	iph->ttl	= net->ipv4.sysctl_ip_default_ttl;
	iph->protocol	= IPPROTO_TCP;
	iph->check	= 0;
	iph->saddr	= saddr;
	iph->daddr	= daddr;

	return iph;
}