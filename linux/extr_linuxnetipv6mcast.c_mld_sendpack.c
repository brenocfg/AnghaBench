#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  igmp_sk; } ;
struct net {TYPE_1__ ipv6; } ;
struct mld2_report {int /*<<< orphan*/  mld2r_cksum; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  payload_len; } ;
struct inet6_dev {int dummy; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6MSGOUT_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_MIB_OUTMSGS ; 
 int /*<<< orphan*/  ICMPV6_MLD2_REPORT ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 int PTR_ERR (struct dst_entry*) ; 
 struct inet6_dev* __in6_dev_get (TYPE_2__*) ; 
 int /*<<< orphan*/  csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (int,int,int /*<<< orphan*/ ) ; 
 struct net* dev_net (TYPE_2__*) ; 
 int /*<<< orphan*/  dst_output ; 
 int /*<<< orphan*/  htons (int) ; 
 struct dst_entry* icmp6_dst_alloc (TYPE_2__*,struct flowi6*) ; 
 int /*<<< orphan*/  icmpv6_flow_init (int /*<<< orphan*/ ,struct flowi6*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int skb_tail_pointer (struct sk_buff*) ; 
 int skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static void mld_sendpack(struct sk_buff *skb)
{
	struct ipv6hdr *pip6 = ipv6_hdr(skb);
	struct mld2_report *pmr =
			      (struct mld2_report *)skb_transport_header(skb);
	int payload_len, mldlen;
	struct inet6_dev *idev;
	struct net *net = dev_net(skb->dev);
	int err;
	struct flowi6 fl6;
	struct dst_entry *dst;

	rcu_read_lock();
	idev = __in6_dev_get(skb->dev);
	IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_OUT, skb->len);

	payload_len = (skb_tail_pointer(skb) - skb_network_header(skb)) -
		sizeof(*pip6);
	mldlen = skb_tail_pointer(skb) - skb_transport_header(skb);
	pip6->payload_len = htons(payload_len);

	pmr->mld2r_cksum = csum_ipv6_magic(&pip6->saddr, &pip6->daddr, mldlen,
					   IPPROTO_ICMPV6,
					   csum_partial(skb_transport_header(skb),
							mldlen, 0));

	icmpv6_flow_init(net->ipv6.igmp_sk, &fl6, ICMPV6_MLD2_REPORT,
			 &ipv6_hdr(skb)->saddr, &ipv6_hdr(skb)->daddr,
			 skb->dev->ifindex);
	dst = icmp6_dst_alloc(skb->dev, &fl6);

	err = 0;
	if (IS_ERR(dst)) {
		err = PTR_ERR(dst);
		dst = NULL;
	}
	skb_dst_set(skb, dst);
	if (err)
		goto err_out;

	err = NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
		      net, net->ipv6.igmp_sk, skb, NULL, skb->dev,
		      dst_output);
out:
	if (!err) {
		ICMP6MSGOUT_INC_STATS(net, idev, ICMPV6_MLD2_REPORT);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	} else {
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCARDS);
	}

	rcu_read_unlock();
	return;

err_out:
	kfree_skb(skb);
	goto out;
}