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
struct sk_buff {scalar_t__ encapsulation; scalar_t__ data; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  gro_complete; } ;
struct net_offload {TYPE_1__ callbacks; } ;
struct iphdr {int protocol; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  check; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int INDIRECT_CALL_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_replace2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/ * inet_offloads ; 
 struct net_offload* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_set_inner_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_inner_protocol (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp4_gro_complete ; 
 int /*<<< orphan*/  udp4_gro_complete ; 

int inet_gro_complete(struct sk_buff *skb, int nhoff)
{
	__be16 newlen = htons(skb->len - nhoff);
	struct iphdr *iph = (struct iphdr *)(skb->data + nhoff);
	const struct net_offload *ops;
	int proto = iph->protocol;
	int err = -ENOSYS;

	if (skb->encapsulation) {
		skb_set_inner_protocol(skb, cpu_to_be16(ETH_P_IP));
		skb_set_inner_network_header(skb, nhoff);
	}

	csum_replace2(&iph->check, iph->tot_len, newlen);
	iph->tot_len = newlen;

	rcu_read_lock();
	ops = rcu_dereference(inet_offloads[proto]);
	if (WARN_ON(!ops || !ops->callbacks.gro_complete))
		goto out_unlock;

	/* Only need to add sizeof(*iph) to get to the next hdr below
	 * because any hdr with option will have been flushed in
	 * inet_gro_receive().
	 */
	err = INDIRECT_CALL_2(ops->callbacks.gro_complete,
			      tcp4_gro_complete, udp4_gro_complete,
			      skb, nhoff + sizeof(*iph));

out_unlock:
	rcu_read_unlock();

	return err;
}