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
struct nf_nat_lookup_hook_priv {int /*<<< orphan*/  entries; } ;
struct nf_hook_state {int /*<<< orphan*/  hook; int /*<<< orphan*/  out; } ;
struct nf_hook_entries {int num_hook_entries; TYPE_1__* hooks; } ;
struct nf_conn_nat {int dummy; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {unsigned int (* hook ) (int /*<<< orphan*/ ,struct sk_buff*,struct nf_hook_state const*) ;int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int HOOK2MANIP (int /*<<< orphan*/ ) ; 
 int IP_CT_ESTABLISHED ; 
 int IP_CT_ESTABLISHED_REPLY ; 
#define  IP_CT_NEW 130 
#define  IP_CT_RELATED 129 
#define  IP_CT_RELATED_REPLY 128 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_kill_acct (struct nf_conn*,int,struct sk_buff*) ; 
 unsigned int nf_nat_alloc_null_binding (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_nat_initialized (struct nf_conn*,int) ; 
 int /*<<< orphan*/  nf_nat_oif_changed (int /*<<< orphan*/ ,int,struct nf_conn_nat*,int /*<<< orphan*/ ) ; 
 unsigned int nf_nat_packet (struct nf_conn*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,struct nf_conn*,int /*<<< orphan*/ ) ; 
 struct nf_hook_entries* rcu_dereference (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct nf_hook_state const*) ; 

unsigned int
nf_nat_inet_fn(void *priv, struct sk_buff *skb,
	       const struct nf_hook_state *state)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	struct nf_conn_nat *nat;
	/* maniptype == SRC for postrouting. */
	enum nf_nat_manip_type maniptype = HOOK2MANIP(state->hook);

	ct = nf_ct_get(skb, &ctinfo);
	/* Can't track?  It's not due to stress, or conntrack would
	 * have dropped it.  Hence it's the user's responsibilty to
	 * packet filter it out, or implement conntrack/NAT for that
	 * protocol. 8) --RR
	 */
	if (!ct)
		return NF_ACCEPT;

	nat = nfct_nat(ct);

	switch (ctinfo) {
	case IP_CT_RELATED:
	case IP_CT_RELATED_REPLY:
		/* Only ICMPs can be IP_CT_IS_REPLY.  Fallthrough */
	case IP_CT_NEW:
		/* Seen it before?  This can happen for loopback, retrans,
		 * or local packets.
		 */
		if (!nf_nat_initialized(ct, maniptype)) {
			struct nf_nat_lookup_hook_priv *lpriv = priv;
			struct nf_hook_entries *e = rcu_dereference(lpriv->entries);
			unsigned int ret;
			int i;

			if (!e)
				goto null_bind;

			for (i = 0; i < e->num_hook_entries; i++) {
				ret = e->hooks[i].hook(e->hooks[i].priv, skb,
						       state);
				if (ret != NF_ACCEPT)
					return ret;
				if (nf_nat_initialized(ct, maniptype))
					goto do_nat;
			}
null_bind:
			ret = nf_nat_alloc_null_binding(ct, state->hook);
			if (ret != NF_ACCEPT)
				return ret;
		} else {
			pr_debug("Already setup manip %s for ct %p (status bits 0x%lx)\n",
				 maniptype == NF_NAT_MANIP_SRC ? "SRC" : "DST",
				 ct, ct->status);
			if (nf_nat_oif_changed(state->hook, ctinfo, nat,
					       state->out))
				goto oif_changed;
		}
		break;
	default:
		/* ESTABLISHED */
		WARN_ON(ctinfo != IP_CT_ESTABLISHED &&
			ctinfo != IP_CT_ESTABLISHED_REPLY);
		if (nf_nat_oif_changed(state->hook, ctinfo, nat, state->out))
			goto oif_changed;
	}
do_nat:
	return nf_nat_packet(ct, ctinfo, state->hook, skb);

oif_changed:
	nf_ct_kill_acct(ct, ctinfo, skb);
	return NF_DROP;
}