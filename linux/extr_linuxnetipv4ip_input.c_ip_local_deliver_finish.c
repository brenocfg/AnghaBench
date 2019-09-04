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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_protocol {int (* handler ) (struct sk_buff*) ;int /*<<< orphan*/  no_policy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_PROT_UNREACH ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDELIVERS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INUNKNOWNPROTOS ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_protos ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int raw_local_deliver (struct sk_buff*,int) ; 
 struct net_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 scalar_t__ xfrm4_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int ip_local_deliver_finish(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	__skb_pull(skb, skb_network_header_len(skb));

	rcu_read_lock();
	{
		int protocol = ip_hdr(skb)->protocol;
		const struct net_protocol *ipprot;
		int raw;

	resubmit:
		raw = raw_local_deliver(skb, protocol);

		ipprot = rcu_dereference(inet_protos[protocol]);
		if (ipprot) {
			int ret;

			if (!ipprot->no_policy) {
				if (!xfrm4_policy_check(NULL, XFRM_POLICY_IN, skb)) {
					kfree_skb(skb);
					goto out;
				}
				nf_reset(skb);
			}
			ret = ipprot->handler(skb);
			if (ret < 0) {
				protocol = -ret;
				goto resubmit;
			}
			__IP_INC_STATS(net, IPSTATS_MIB_INDELIVERS);
		} else {
			if (!raw) {
				if (xfrm4_policy_check(NULL, XFRM_POLICY_IN, skb)) {
					__IP_INC_STATS(net, IPSTATS_MIB_INUNKNOWNPROTOS);
					icmp_send(skb, ICMP_DEST_UNREACH,
						  ICMP_PROT_UNREACH, 0);
				}
				kfree_skb(skb);
			} else {
				__IP_INC_STATS(net, IPSTATS_MIB_INDELIVERS);
				consume_skb(skb);
			}
		}
	}
 out:
	rcu_read_unlock();

	return 0;
}