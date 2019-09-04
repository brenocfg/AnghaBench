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
struct nlattr {int dummy; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nft_ct {int dir; int key; int /*<<< orphan*/  sreg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IP_CT_DIR_MAX ; 
#define  IP_CT_DIR_ORIGINAL 129 
#define  IP_CT_DIR_REPLY 128 
 size_t NFTA_CT_DIRECTION ; 
 size_t NFTA_CT_KEY ; 
 size_t NFTA_CT_SREG ; 
 int /*<<< orphan*/  __nft_ct_set_destroy (struct nft_ctx const*,struct nft_ct*) ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_ct* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int nla_get_u8 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_ct_set_init(const struct nft_ctx *ctx,
			   const struct nft_expr *expr,
			   const struct nlattr * const tb[])
{
	struct nft_ct *priv = nft_expr_priv(expr);
	unsigned int len;
	int err;

	priv->dir = IP_CT_DIR_MAX;
	priv->key = ntohl(nla_get_be32(tb[NFTA_CT_KEY]));
	switch (priv->key) {
#ifdef CONFIG_NF_CONNTRACK_MARK
	case NFT_CT_MARK:
		if (tb[NFTA_CT_DIRECTION])
			return -EINVAL;
		len = FIELD_SIZEOF(struct nf_conn, mark);
		break;
#endif
#ifdef CONFIG_NF_CONNTRACK_LABELS
	case NFT_CT_LABELS:
		if (tb[NFTA_CT_DIRECTION])
			return -EINVAL;
		len = NF_CT_LABELS_MAX_SIZE;
		err = nf_connlabels_get(ctx->net, (len * BITS_PER_BYTE) - 1);
		if (err)
			return err;
		break;
#endif
#ifdef CONFIG_NF_CONNTRACK_ZONES
	case NFT_CT_ZONE:
		if (!nft_ct_tmpl_alloc_pcpu())
			return -ENOMEM;
		nft_ct_pcpu_template_refcnt++;
		len = sizeof(u16);
		break;
#endif
#ifdef CONFIG_NF_CONNTRACK_EVENTS
	case NFT_CT_EVENTMASK:
		if (tb[NFTA_CT_DIRECTION])
			return -EINVAL;
		len = sizeof(u32);
		break;
#endif
	default:
		return -EOPNOTSUPP;
	}

	if (tb[NFTA_CT_DIRECTION]) {
		priv->dir = nla_get_u8(tb[NFTA_CT_DIRECTION]);
		switch (priv->dir) {
		case IP_CT_DIR_ORIGINAL:
		case IP_CT_DIR_REPLY:
			break;
		default:
			err = -EINVAL;
			goto err1;
		}
	}

	priv->sreg = nft_parse_register(tb[NFTA_CT_SREG]);
	err = nft_validate_register_load(priv->sreg, len);
	if (err < 0)
		goto err1;

	err = nf_ct_netns_get(ctx->net, ctx->family);
	if (err < 0)
		goto err1;

	return 0;

err1:
	__nft_ct_set_destroy(ctx, priv);
	return err;
}