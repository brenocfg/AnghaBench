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
struct tcf_result {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  overlimits; } ;
struct tcf_connmark_info {int tcf_action; int /*<<< orphan*/  tcf_lock; TYPE_1__ tcf_qstats; int /*<<< orphan*/  net; int /*<<< orphan*/  zone; int /*<<< orphan*/  tcf_bstats; int /*<<< orphan*/  tcf_tm; } ;
struct tc_action {int dummy; } ;
struct sk_buff {scalar_t__ protocol; int len; int /*<<< orphan*/  mark; } ;
struct nf_conntrack_zone {int /*<<< orphan*/  dir; int /*<<< orphan*/  id; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  mark; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int NFPROTO_IPV4 ; 
 int NFPROTO_IPV6 ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_DIR ; 
 int /*<<< orphan*/  bstats_update (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (int /*<<< orphan*/ ,struct nf_conntrack_zone*,struct nf_conntrack_tuple*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 struct tcf_connmark_info* to_connmark (struct tc_action const*) ; 

__attribute__((used)) static int tcf_connmark_act(struct sk_buff *skb, const struct tc_action *a,
			    struct tcf_result *res)
{
	const struct nf_conntrack_tuple_hash *thash;
	struct nf_conntrack_tuple tuple;
	enum ip_conntrack_info ctinfo;
	struct tcf_connmark_info *ca = to_connmark(a);
	struct nf_conntrack_zone zone;
	struct nf_conn *c;
	int proto;

	spin_lock(&ca->tcf_lock);
	tcf_lastuse_update(&ca->tcf_tm);
	bstats_update(&ca->tcf_bstats, skb);

	if (skb->protocol == htons(ETH_P_IP)) {
		if (skb->len < sizeof(struct iphdr))
			goto out;

		proto = NFPROTO_IPV4;
	} else if (skb->protocol == htons(ETH_P_IPV6)) {
		if (skb->len < sizeof(struct ipv6hdr))
			goto out;

		proto = NFPROTO_IPV6;
	} else {
		goto out;
	}

	c = nf_ct_get(skb, &ctinfo);
	if (c) {
		skb->mark = c->mark;
		/* using overlimits stats to count how many packets marked */
		ca->tcf_qstats.overlimits++;
		goto out;
	}

	if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
			       proto, ca->net, &tuple))
		goto out;

	zone.id = ca->zone;
	zone.dir = NF_CT_DEFAULT_ZONE_DIR;

	thash = nf_conntrack_find_get(ca->net, &zone, &tuple);
	if (!thash)
		goto out;

	c = nf_ct_tuplehash_to_ctrack(thash);
	/* using overlimits stats to count how many packets marked */
	ca->tcf_qstats.overlimits++;
	skb->mark = c->mark;
	nf_ct_put(c);

out:
	spin_unlock(&ca->tcf_lock);
	return ca->tcf_action;
}