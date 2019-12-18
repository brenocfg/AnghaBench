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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {int hop_limit; struct in6_addr daddr; struct in6_addr saddr; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  payload_len; } ;
struct TYPE_2__ {unsigned int ndisc_tclass; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  ip6_flow_hdr (struct ipv6hdr*,unsigned int,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void ip6_nd_hdr(struct sk_buff *skb,
		       const struct in6_addr *saddr,
		       const struct in6_addr *daddr,
		       int hop_limit, int len)
{
	struct ipv6hdr *hdr;
	struct inet6_dev *idev;
	unsigned tclass;

	rcu_read_lock();
	idev = __in6_dev_get(skb->dev);
	tclass = idev ? idev->cnf.ndisc_tclass : 0;
	rcu_read_unlock();

	skb_push(skb, sizeof(*hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	ip6_flow_hdr(hdr, tclass, 0);

	hdr->payload_len = htons(len);
	hdr->nexthdr = IPPROTO_ICMPV6;
	hdr->hop_limit = hop_limit;

	hdr->saddr = *saddr;
	hdr->daddr = *daddr;
}