#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcphdr {int /*<<< orphan*/  check; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 scalar_t__ skb_try_make_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int nf_flow_nat_ip_tcp(struct sk_buff *skb, unsigned int thoff,
			      __be32 addr, __be32 new_addr)
{
	struct tcphdr *tcph;

	if (!pskb_may_pull(skb, thoff + sizeof(*tcph)) ||
	    skb_try_make_writable(skb, thoff + sizeof(*tcph)))
		return -1;

	tcph = (void *)(skb_network_header(skb) + thoff);
	inet_proto_csum_replace4(&tcph->check, skb, addr, new_addr, true);

	return 0;
}