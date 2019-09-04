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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {scalar_t__ _nfct; } ;
struct nf_conntrack_l4proto {int (* error ) (struct net*,struct nf_conn*,struct sk_buff*,int,int /*<<< orphan*/ ,unsigned int) ;int (* packet ) (struct nf_conn*,struct sk_buff*,int,int) ;} ;
struct nf_conn {int /*<<< orphan*/  status; int /*<<< orphan*/  ct_general; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_REPLY ; 
 int /*<<< orphan*/  IPS_SEEN_REPLY_BIT ; 
 int IP_CT_ESTABLISHED_REPLY ; 
 int IP_CT_UNTRACKED ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_CT_STAT_INC_ATOMIC (struct net*,int /*<<< orphan*/ ) ; 
 int NF_DROP ; 
 int NF_REPEAT ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop ; 
 int /*<<< orphan*/  error ; 
 int get_l4proto (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ignore ; 
 int /*<<< orphan*/  invalid ; 
 int /*<<< orphan*/  nf_conntrack_event_cache (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_conntrack_put (int /*<<< orphan*/ *) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_is_template (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int resolve_normal_ct (struct net*,struct nf_conn*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_l4proto const*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int stub1 (struct net*,struct nf_conn*,struct sk_buff*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int stub2 (struct nf_conn*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned int
nf_conntrack_in(struct net *net, u_int8_t pf, unsigned int hooknum,
		struct sk_buff *skb)
{
	const struct nf_conntrack_l4proto *l4proto;
	struct nf_conn *ct, *tmpl;
	enum ip_conntrack_info ctinfo;
	u_int8_t protonum;
	int dataoff, ret;

	tmpl = nf_ct_get(skb, &ctinfo);
	if (tmpl || ctinfo == IP_CT_UNTRACKED) {
		/* Previously seen (loopback or untracked)?  Ignore. */
		if ((tmpl && !nf_ct_is_template(tmpl)) ||
		     ctinfo == IP_CT_UNTRACKED) {
			NF_CT_STAT_INC_ATOMIC(net, ignore);
			return NF_ACCEPT;
		}
		skb->_nfct = 0;
	}

	/* rcu_read_lock()ed by nf_hook_thresh */
	dataoff = get_l4proto(skb, skb_network_offset(skb), pf, &protonum);
	if (dataoff <= 0) {
		pr_debug("not prepared to track yet or error occurred\n");
		NF_CT_STAT_INC_ATOMIC(net, error);
		NF_CT_STAT_INC_ATOMIC(net, invalid);
		ret = NF_ACCEPT;
		goto out;
	}

	l4proto = __nf_ct_l4proto_find(pf, protonum);

	/* It may be an special packet, error, unclean...
	 * inverse of the return code tells to the netfilter
	 * core what to do with the packet. */
	if (l4proto->error != NULL) {
		ret = l4proto->error(net, tmpl, skb, dataoff, pf, hooknum);
		if (ret <= 0) {
			NF_CT_STAT_INC_ATOMIC(net, error);
			NF_CT_STAT_INC_ATOMIC(net, invalid);
			ret = -ret;
			goto out;
		}
		/* ICMP[v6] protocol trackers may assign one conntrack. */
		if (skb->_nfct)
			goto out;
	}
repeat:
	ret = resolve_normal_ct(net, tmpl, skb, dataoff, pf, protonum, l4proto);
	if (ret < 0) {
		/* Too stressed to deal. */
		NF_CT_STAT_INC_ATOMIC(net, drop);
		ret = NF_DROP;
		goto out;
	}

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct) {
		/* Not valid part of a connection */
		NF_CT_STAT_INC_ATOMIC(net, invalid);
		ret = NF_ACCEPT;
		goto out;
	}

	ret = l4proto->packet(ct, skb, dataoff, ctinfo);
	if (ret <= 0) {
		/* Invalid: inverse of the return code tells
		 * the netfilter core what to do */
		pr_debug("nf_conntrack_in: Can't track with proto module\n");
		nf_conntrack_put(&ct->ct_general);
		skb->_nfct = 0;
		NF_CT_STAT_INC_ATOMIC(net, invalid);
		if (ret == -NF_DROP)
			NF_CT_STAT_INC_ATOMIC(net, drop);
		/* Special case: TCP tracker reports an attempt to reopen a
		 * closed/aborted connection. We have to go back and create a
		 * fresh conntrack.
		 */
		if (ret == -NF_REPEAT)
			goto repeat;
		ret = -ret;
		goto out;
	}

	if (ctinfo == IP_CT_ESTABLISHED_REPLY &&
	    !test_and_set_bit(IPS_SEEN_REPLY_BIT, &ct->status))
		nf_conntrack_event_cache(IPCT_REPLY, ct);
out:
	if (tmpl)
		nf_ct_put(tmpl);

	return ret;
}