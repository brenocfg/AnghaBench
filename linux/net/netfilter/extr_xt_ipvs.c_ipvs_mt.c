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
typedef  int /*<<< orphan*/  u_int8_t ;
struct xt_ipvs_mtinfo {int bitmask; int invert; scalar_t__ l4proto; scalar_t__ vport; scalar_t__ vportctl; int fwd_method; int /*<<< orphan*/  vmask; int /*<<< orphan*/  vaddr; } ;
struct xt_action_param {struct xt_ipvs_mtinfo* matchinfo; } ;
struct sk_buff {int ipvs_property; } ;
struct nf_conn {int dummy; } ;
struct netns_ipvs {int dummy; } ;
struct ip_vs_protocol {struct ip_vs_conn* (* conn_out_get ) (struct netns_ipvs*,int /*<<< orphan*/  const,struct sk_buff const*,struct ip_vs_iphdr*) ;} ;
struct ip_vs_iphdr {scalar_t__ protocol; } ;
struct ip_vs_conn {scalar_t__ vport; int flags; int /*<<< orphan*/  vaddr; TYPE_1__* control; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {scalar_t__ vport; } ;

/* Variables and functions */
 int IP_CT_IS_REPLY ; 
 int IP_VS_CONN_F_FWD_MASK ; 
 int XT_IPVS_DIR ; 
 int XT_IPVS_IPVS_PROPERTY ; 
 int XT_IPVS_METHOD ; 
 int XT_IPVS_PROTO ; 
 int XT_IPVS_VADDR ; 
 int XT_IPVS_VPORT ; 
 int XT_IPVS_VPORTCTL ; 
 int /*<<< orphan*/  __ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_fill_iph_skb (int /*<<< orphan*/  const,struct sk_buff const*,int,struct ip_vs_iphdr*) ; 
 struct ip_vs_protocol* ip_vs_proto_get (scalar_t__) ; 
 int ipvs_mt_addrcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 struct netns_ipvs* net_ipvs (int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct ip_vs_conn* stub1 (struct netns_ipvs*,int /*<<< orphan*/  const,struct sk_buff const*,struct ip_vs_iphdr*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xt_family (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool
ipvs_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_ipvs_mtinfo *data = par->matchinfo;
	struct netns_ipvs *ipvs = net_ipvs(xt_net(par));
	/* ipvs_mt_check ensures that family is only NFPROTO_IPV[46]. */
	const u_int8_t family = xt_family(par);
	struct ip_vs_iphdr iph;
	struct ip_vs_protocol *pp;
	struct ip_vs_conn *cp;
	bool match = true;

	if (data->bitmask == XT_IPVS_IPVS_PROPERTY) {
		match = skb->ipvs_property ^
			!!(data->invert & XT_IPVS_IPVS_PROPERTY);
		goto out;
	}

	/* other flags than XT_IPVS_IPVS_PROPERTY are set */
	if (!skb->ipvs_property) {
		match = false;
		goto out;
	}

	ip_vs_fill_iph_skb(family, skb, true, &iph);

	if (data->bitmask & XT_IPVS_PROTO)
		if ((iph.protocol == data->l4proto) ^
		    !(data->invert & XT_IPVS_PROTO)) {
			match = false;
			goto out;
		}

	pp = ip_vs_proto_get(iph.protocol);
	if (unlikely(!pp)) {
		match = false;
		goto out;
	}

	/*
	 * Check if the packet belongs to an existing entry
	 */
	cp = pp->conn_out_get(ipvs, family, skb, &iph);
	if (unlikely(cp == NULL)) {
		match = false;
		goto out;
	}

	/*
	 * We found a connection, i.e. ct != 0, make sure to call
	 * __ip_vs_conn_put before returning.  In our case jump to out_put_con.
	 */

	if (data->bitmask & XT_IPVS_VPORT)
		if ((cp->vport == data->vport) ^
		    !(data->invert & XT_IPVS_VPORT)) {
			match = false;
			goto out_put_cp;
		}

	if (data->bitmask & XT_IPVS_VPORTCTL)
		if ((cp->control != NULL &&
		     cp->control->vport == data->vportctl) ^
		    !(data->invert & XT_IPVS_VPORTCTL)) {
			match = false;
			goto out_put_cp;
		}

	if (data->bitmask & XT_IPVS_DIR) {
		enum ip_conntrack_info ctinfo;
		struct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		if (ct == NULL) {
			match = false;
			goto out_put_cp;
		}

		if ((ctinfo >= IP_CT_IS_REPLY) ^
		    !!(data->invert & XT_IPVS_DIR)) {
			match = false;
			goto out_put_cp;
		}
	}

	if (data->bitmask & XT_IPVS_METHOD)
		if (((cp->flags & IP_VS_CONN_F_FWD_MASK) == data->fwd_method) ^
		    !(data->invert & XT_IPVS_METHOD)) {
			match = false;
			goto out_put_cp;
		}

	if (data->bitmask & XT_IPVS_VADDR) {
		if (ipvs_mt_addrcmp(&cp->vaddr, &data->vaddr,
				    &data->vmask, family) ^
		    !(data->invert & XT_IPVS_VADDR)) {
			match = false;
			goto out_put_cp;
		}
	}

out_put_cp:
	__ip_vs_conn_put(cp);
out:
	pr_debug("match=%d\n", match);
	return match;
}