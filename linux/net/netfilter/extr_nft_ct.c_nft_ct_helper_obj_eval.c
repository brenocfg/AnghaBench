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
struct nft_regs {int dummy; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_object {int dummy; } ;
struct nft_ct_helper_obj {scalar_t__ l4proto; struct nf_conntrack_helper* helper6; struct nf_conntrack_helper* helper4; } ;
struct nf_conntrack_helper {int dummy; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPS_HELPER_BIT ; 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nf_conn_help* nf_ct_helper_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_is_confirmed (struct nf_conn*) ; 
 scalar_t__ nf_ct_is_template (struct nf_conn*) ; 
 int nf_ct_l3num (struct nf_conn*) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 
 struct nft_ct_helper_obj* nft_obj_data (struct nft_object*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_nfct (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nft_ct_helper_obj_eval(struct nft_object *obj,
				   struct nft_regs *regs,
				   const struct nft_pktinfo *pkt)
{
	const struct nft_ct_helper_obj *priv = nft_obj_data(obj);
	struct nf_conn *ct = (struct nf_conn *)skb_nfct(pkt->skb);
	struct nf_conntrack_helper *to_assign = NULL;
	struct nf_conn_help *help;

	if (!ct ||
	    nf_ct_is_confirmed(ct) ||
	    nf_ct_is_template(ct) ||
	    priv->l4proto != nf_ct_protonum(ct))
		return;

	switch (nf_ct_l3num(ct)) {
	case NFPROTO_IPV4:
		to_assign = priv->helper4;
		break;
	case NFPROTO_IPV6:
		to_assign = priv->helper6;
		break;
	default:
		WARN_ON_ONCE(1);
		return;
	}

	if (!to_assign)
		return;

	if (test_bit(IPS_HELPER_BIT, &ct->status))
		return;

	help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
	if (help) {
		rcu_assign_pointer(help->helper, to_assign);
		set_bit(IPS_HELPER_BIT, &ct->status);
	}
}