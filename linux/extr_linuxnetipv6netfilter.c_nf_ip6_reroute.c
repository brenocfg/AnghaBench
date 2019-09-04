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
struct sk_buff {scalar_t__ mark; } ;
struct TYPE_2__ {scalar_t__ hook; int /*<<< orphan*/  net; } ;
struct nf_queue_entry {TYPE_1__ state; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ip6_rt_info {scalar_t__ mark; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 scalar_t__ NF_INET_LOCAL_OUT ; 
 int ip6_route_me_harder (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 struct ip6_rt_info* nf_queue_entry_reroute (struct nf_queue_entry const*) ; 

__attribute__((used)) static int nf_ip6_reroute(struct sk_buff *skb,
			  const struct nf_queue_entry *entry)
{
	struct ip6_rt_info *rt_info = nf_queue_entry_reroute(entry);

	if (entry->state.hook == NF_INET_LOCAL_OUT) {
		const struct ipv6hdr *iph = ipv6_hdr(skb);
		if (!ipv6_addr_equal(&iph->daddr, &rt_info->daddr) ||
		    !ipv6_addr_equal(&iph->saddr, &rt_info->saddr) ||
		    skb->mark != rt_info->mark)
			return ip6_route_me_harder(entry->state.net, skb);
	}
	return 0;
}