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
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  protonum; } ;
struct nf_conntrack_tuple {TYPE_1__ dst; } ;
struct nf_conntrack_l4proto {int dummy; } ;
struct nf_conn {int dummy; } ;
struct net {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct icmp6hdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 scalar_t__ IP_CT_DIR_REPLY ; 
 scalar_t__ IP_CT_IS_REPLY ; 
 int IP_CT_RELATED ; 
 int NF_ACCEPT ; 
 scalar_t__ NF_CT_DIRECTION (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (struct net*,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,struct net*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,struct nf_conntrack_tuple*,struct nf_conntrack_l4proto const*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  nf_ct_zone_tmpl (struct nf_conn*,struct sk_buff*,struct nf_conntrack_zone*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_nfct (struct sk_buff*) ; 

__attribute__((used)) static int
icmpv6_error_message(struct net *net, struct nf_conn *tmpl,
		     struct sk_buff *skb,
		     unsigned int icmp6off)
{
	struct nf_conntrack_tuple intuple, origtuple;
	const struct nf_conntrack_tuple_hash *h;
	const struct nf_conntrack_l4proto *inproto;
	enum ip_conntrack_info ctinfo;
	struct nf_conntrack_zone tmp;

	WARN_ON(skb_nfct(skb));

	/* Are they talking about one of our connections? */
	if (!nf_ct_get_tuplepr(skb,
			       skb_network_offset(skb)
				+ sizeof(struct ipv6hdr)
				+ sizeof(struct icmp6hdr),
			       PF_INET6, net, &origtuple)) {
		pr_debug("icmpv6_error: Can't get tuple\n");
		return -NF_ACCEPT;
	}

	/* rcu_read_lock()ed by nf_hook_thresh */
	inproto = __nf_ct_l4proto_find(PF_INET6, origtuple.dst.protonum);

	/* Ordinarily, we'd expect the inverted tupleproto, but it's
	   been preserved inside the ICMP. */
	if (!nf_ct_invert_tuple(&intuple, &origtuple, inproto)) {
		pr_debug("icmpv6_error: Can't invert tuple\n");
		return -NF_ACCEPT;
	}

	ctinfo = IP_CT_RELATED;

	h = nf_conntrack_find_get(net, nf_ct_zone_tmpl(tmpl, skb, &tmp),
				  &intuple);
	if (!h) {
		pr_debug("icmpv6_error: no match\n");
		return -NF_ACCEPT;
	} else {
		if (NF_CT_DIRECTION(h) == IP_CT_DIR_REPLY)
			ctinfo += IP_CT_IS_REPLY;
	}

	/* Update skb to refer to this connection */
	nf_ct_set(skb, nf_ct_tuplehash_to_ctrack(h), ctinfo);
	return NF_ACCEPT;
}