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
struct nft_ctx {int dummy; } ;
struct nft_ct {int key; } ;

/* Variables and functions */

__attribute__((used)) static void __nft_ct_set_destroy(const struct nft_ctx *ctx, struct nft_ct *priv)
{
	switch (priv->key) {
#ifdef CONFIG_NF_CONNTRACK_LABELS
	case NFT_CT_LABELS:
		nf_connlabels_put(ctx->net);
		break;
#endif
#ifdef CONFIG_NF_CONNTRACK_ZONES
	case NFT_CT_ZONE:
		if (--nft_ct_pcpu_template_refcnt == 0)
			nft_ct_tmpl_put_pcpu();
#endif
	default:
		break;
	}
}