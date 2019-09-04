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
struct sk_buff {int dummy; } ;
struct nft_regs {int dummy; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_expr {int dummy; } ;
struct nft_ct {int key; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 scalar_t__ nf_ct_is_template (struct nf_conn*) ; 
 struct nft_ct* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static void nft_ct_set_eval(const struct nft_expr *expr,
			    struct nft_regs *regs,
			    const struct nft_pktinfo *pkt)
{
	const struct nft_ct *priv = nft_expr_priv(expr);
	struct sk_buff *skb = pkt->skb;
#ifdef CONFIG_NF_CONNTRACK_MARK
	u32 value = regs->data[priv->sreg];
#endif
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL || nf_ct_is_template(ct))
		return;

	switch (priv->key) {
#ifdef CONFIG_NF_CONNTRACK_MARK
	case NFT_CT_MARK:
		if (ct->mark != value) {
			ct->mark = value;
			nf_conntrack_event_cache(IPCT_MARK, ct);
		}
		break;
#endif
#ifdef CONFIG_NF_CONNTRACK_LABELS
	case NFT_CT_LABELS:
		nf_connlabels_replace(ct,
				      &regs->data[priv->sreg],
				      &regs->data[priv->sreg],
				      NF_CT_LABELS_MAX_SIZE / sizeof(u32));
		break;
#endif
#ifdef CONFIG_NF_CONNTRACK_EVENTS
	case NFT_CT_EVENTMASK: {
		struct nf_conntrack_ecache *e = nf_ct_ecache_find(ct);
		u32 ctmask = regs->data[priv->sreg];

		if (e) {
			if (e->ctmask != ctmask)
				e->ctmask = ctmask;
			break;
		}

		if (ctmask && !nf_ct_is_confirmed(ct))
			nf_ct_ecache_ext_add(ct, ctmask, 0, GFP_ATOMIC);
		break;
	}
#endif
	default:
		break;
	}
}