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
struct sk_buff {int len; scalar_t__ encapsulation; scalar_t__ data; } ;
struct TYPE_2__ {int (* gro_complete ) (struct sk_buff*,int) ;} ;
struct net_offload {TYPE_1__ callbacks; } ;
struct ipv6hdr {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ ipv6_exthdrs_len (struct ipv6hdr*,struct net_offload const**) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_set_inner_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_inner_protocol (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,int) ; 

__attribute__((used)) static int ipv6_gro_complete(struct sk_buff *skb, int nhoff)
{
	const struct net_offload *ops;
	struct ipv6hdr *iph = (struct ipv6hdr *)(skb->data + nhoff);
	int err = -ENOSYS;

	if (skb->encapsulation) {
		skb_set_inner_protocol(skb, cpu_to_be16(ETH_P_IPV6));
		skb_set_inner_network_header(skb, nhoff);
	}

	iph->payload_len = htons(skb->len - nhoff - sizeof(*iph));

	rcu_read_lock();

	nhoff += sizeof(*iph) + ipv6_exthdrs_len(iph, &ops);
	if (WARN_ON(!ops || !ops->callbacks.gro_complete))
		goto out_unlock;

	err = ops->callbacks.gro_complete(skb, nhoff);

out_unlock:
	rcu_read_unlock();

	return err;
}