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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ovs_conntrack_info {scalar_t__ helper; scalar_t__ nf_ct_timeout; scalar_t__ force; int /*<<< orphan*/  ct; } ;
struct nf_conn_timeout {int /*<<< orphan*/  timeout; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int /*<<< orphan*/  ct_general; int /*<<< orphan*/  ct_net; } ;
struct net {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 scalar_t__ CTINFO2DIR (int) ; 
 scalar_t__ IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  NF_CT_EXT_HELPER ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_conntrack_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_delete (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn_help* nf_ct_ext_find (struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nf_conn_timeout* nf_ct_timeout_find (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_zone (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_zone_equal_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn* ovs_ct_executed (struct net*,struct sw_flow_key const*,struct ovs_conntrack_info const*,struct sk_buff*,int*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool skb_nfct_cached(struct net *net,
			    const struct sw_flow_key *key,
			    const struct ovs_conntrack_info *info,
			    struct sk_buff *skb)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;
	bool ct_executed = true;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		ct = ovs_ct_executed(net, key, info, skb, &ct_executed);

	if (ct)
		nf_ct_get(skb, &ctinfo);
	else
		return false;

	if (!net_eq(net, read_pnet(&ct->ct_net)))
		return false;
	if (!nf_ct_zone_equal_any(info->ct, nf_ct_zone(ct)))
		return false;
	if (info->helper) {
		struct nf_conn_help *help;

		help = nf_ct_ext_find(ct, NF_CT_EXT_HELPER);
		if (help && rcu_access_pointer(help->helper) != info->helper)
			return false;
	}
	if (info->nf_ct_timeout) {
		struct nf_conn_timeout *timeout_ext;

		timeout_ext = nf_ct_timeout_find(ct);
		if (!timeout_ext || info->nf_ct_timeout !=
		    rcu_dereference(timeout_ext->timeout))
			return false;
	}
	/* Force conntrack entry direction to the current packet? */
	if (info->force && CTINFO2DIR(ctinfo) != IP_CT_DIR_ORIGINAL) {
		/* Delete the conntrack entry if confirmed, else just release
		 * the reference.
		 */
		if (nf_ct_is_confirmed(ct))
			nf_ct_delete(ct, 0, 0);

		nf_conntrack_put(&ct->ct_general);
		nf_ct_set(skb, NULL, 0);
		return false;
	}

	return ct_executed;
}