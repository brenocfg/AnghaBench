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
struct tcf_result {int dummy; } ;
struct tcf_ctinfo_params {int mode; int dscpstatemask; int /*<<< orphan*/  net; int /*<<< orphan*/  zone; } ;
struct tcf_ctinfo {int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bstats; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  params; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_zone {int /*<<< orphan*/  dir; int /*<<< orphan*/  id; } ;
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conn {int mark; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int CTINFO_MODE_CPMARK ; 
 int CTINFO_MODE_DSCP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int NFPROTO_IPV4 ; 
 int NFPROTO_IPV6 ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_DIR ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstats_update (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_tuple_hash* nf_conntrack_find_get (int /*<<< orphan*/ ,struct nf_conntrack_zone*,struct nf_conntrack_tuple*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_get_tuplepr (struct sk_buff*,int,int,int /*<<< orphan*/ ,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash const*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct tcf_ctinfo_params* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ tc_skb_protocol (struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_ctinfo_cpmark_set (struct nf_conn*,struct tcf_ctinfo*,struct tcf_ctinfo_params*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_ctinfo_dscp_set (struct nf_conn*,struct tcf_ctinfo*,struct tcf_ctinfo_params*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 struct tcf_ctinfo* to_ctinfo (struct tc_action const*) ; 

__attribute__((used)) static int tcf_ctinfo_act(struct sk_buff *skb, const struct tc_action *a,
			  struct tcf_result *res)
{
	const struct nf_conntrack_tuple_hash *thash = NULL;
	struct tcf_ctinfo *ca = to_ctinfo(a);
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_zone zone;
	enum ip_conntrack_info ctinfo;
	struct tcf_ctinfo_params *cp;
	struct nf_conn *ct;
	int proto, wlen;
	int action;

	cp = rcu_dereference_bh(ca->params);

	tcf_lastuse_update(&ca->tcf_tm);
	bstats_update(&ca->tcf_bstats, skb);
	action = READ_ONCE(ca->tcf_action);

	wlen = skb_network_offset(skb);
	if (tc_skb_protocol(skb) == htons(ETH_P_IP)) {
		wlen += sizeof(struct iphdr);
		if (!pskb_may_pull(skb, wlen))
			goto out;

		proto = NFPROTO_IPV4;
	} else if (tc_skb_protocol(skb) == htons(ETH_P_IPV6)) {
		wlen += sizeof(struct ipv6hdr);
		if (!pskb_may_pull(skb, wlen))
			goto out;

		proto = NFPROTO_IPV6;
	} else {
		goto out;
	}

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct) { /* look harder, usually ingress */
		if (!nf_ct_get_tuplepr(skb, skb_network_offset(skb),
				       proto, cp->net, &tuple))
			goto out;
		zone.id = cp->zone;
		zone.dir = NF_CT_DEFAULT_ZONE_DIR;

		thash = nf_conntrack_find_get(cp->net, &zone, &tuple);
		if (!thash)
			goto out;

		ct = nf_ct_tuplehash_to_ctrack(thash);
	}

	if (cp->mode & CTINFO_MODE_DSCP)
		if (!cp->dscpstatemask || (ct->mark & cp->dscpstatemask))
			tcf_ctinfo_dscp_set(ct, ca, cp, skb, wlen, proto);

	if (cp->mode & CTINFO_MODE_CPMARK)
		tcf_ctinfo_cpmark_set(ct, ca, cp, skb);

	if (thash)
		nf_ct_put(ct);
out:
	return action;
}