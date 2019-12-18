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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct inet6_protocol {int flags; int /*<<< orphan*/  handler; } ;
struct inet6_dev {int dummy; } ;
struct TYPE_2__ {unsigned int nhoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_PARAMPROB ; 
 int /*<<< orphan*/  ICMPV6_UNK_NEXTHDR ; 
 int INDIRECT_CALL_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int INET6_PROTO_FINAL ; 
 int INET6_PROTO_NOPOLICY ; 
 TYPE_1__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDELIVERS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INUNKNOWNPROTOS ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  __IP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * inet6_protos ; 
 int inet6_sdif (struct sk_buff*) ; 
 struct inet6_dev* ip6_dst_idev (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_chk_mcast_addr (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_is_mld (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int raw6_local_deliver (struct sk_buff*,int) ; 
 struct inet6_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_rcv ; 
 int /*<<< orphan*/  udpv6_rcv ; 
 scalar_t__ xfrm6_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

void ip6_protocol_deliver_rcu(struct net *net, struct sk_buff *skb, int nexthdr,
			      bool have_final)
{
	const struct inet6_protocol *ipprot;
	struct inet6_dev *idev;
	unsigned int nhoff;
	bool raw;

	/*
	 *	Parse extension headers
	 */

resubmit:
	idev = ip6_dst_idev(skb_dst(skb));
	nhoff = IP6CB(skb)->nhoff;
	if (!have_final) {
		if (!pskb_pull(skb, skb_transport_offset(skb)))
			goto discard;
		nexthdr = skb_network_header(skb)[nhoff];
	}

resubmit_final:
	raw = raw6_local_deliver(skb, nexthdr);
	ipprot = rcu_dereference(inet6_protos[nexthdr]);
	if (ipprot) {
		int ret;

		if (have_final) {
			if (!(ipprot->flags & INET6_PROTO_FINAL)) {
				/* Once we've seen a final protocol don't
				 * allow encapsulation on any non-final
				 * ones. This allows foo in UDP encapsulation
				 * to work.
				 */
				goto discard;
			}
		} else if (ipprot->flags & INET6_PROTO_FINAL) {
			const struct ipv6hdr *hdr;
			int sdif = inet6_sdif(skb);
			struct net_device *dev;

			/* Only do this once for first final protocol */
			have_final = true;

			/* Free reference early: we don't need it any more,
			   and it may hold ip_conntrack module loaded
			   indefinitely. */
			nf_reset_ct(skb);

			skb_postpull_rcsum(skb, skb_network_header(skb),
					   skb_network_header_len(skb));
			hdr = ipv6_hdr(skb);

			/* skb->dev passed may be master dev for vrfs. */
			if (sdif) {
				dev = dev_get_by_index_rcu(net, sdif);
				if (!dev)
					goto discard;
			} else {
				dev = skb->dev;
			}

			if (ipv6_addr_is_multicast(&hdr->daddr) &&
			    !ipv6_chk_mcast_addr(dev, &hdr->daddr,
						 &hdr->saddr) &&
			    !ipv6_is_mld(skb, nexthdr, skb_network_header_len(skb)))
				goto discard;
		}
		if (!(ipprot->flags & INET6_PROTO_NOPOLICY) &&
		    !xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
			goto discard;

		ret = INDIRECT_CALL_2(ipprot->handler, tcp_v6_rcv, udpv6_rcv,
				      skb);
		if (ret > 0) {
			if (ipprot->flags & INET6_PROTO_FINAL) {
				/* Not an extension header, most likely UDP
				 * encapsulation. Use return value as nexthdr
				 * protocol not nhoff (which presumably is
				 * not set by handler).
				 */
				nexthdr = ret;
				goto resubmit_final;
			} else {
				goto resubmit;
			}
		} else if (ret == 0) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDELIVERS);
		}
	} else {
		if (!raw) {
			if (xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb)) {
				__IP6_INC_STATS(net, idev,
						IPSTATS_MIB_INUNKNOWNPROTOS);
				icmpv6_send(skb, ICMPV6_PARAMPROB,
					    ICMPV6_UNK_NEXTHDR, nhoff);
			}
			kfree_skb(skb);
		} else {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDELIVERS);
			consume_skb(skb);
		}
	}
	return;

discard:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INDISCARDS);
	kfree_skb(skb);
}