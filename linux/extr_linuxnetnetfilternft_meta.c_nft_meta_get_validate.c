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
struct nft_expr {int dummy; } ;
struct nft_data {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int nft_meta_get_validate(const struct nft_ctx *ctx,
				 const struct nft_expr *expr,
				 const struct nft_data **data)
{
#ifdef CONFIG_XFRM
	const struct nft_meta *priv = nft_expr_priv(expr);
	unsigned int hooks;

	if (priv->key != NFT_META_SECPATH)
		return 0;

	switch (ctx->family) {
	case NFPROTO_NETDEV:
		hooks = 1 << NF_NETDEV_INGRESS;
		break;
	case NFPROTO_IPV4:
	case NFPROTO_IPV6:
	case NFPROTO_INET:
		hooks = (1 << NF_INET_PRE_ROUTING) |
			(1 << NF_INET_LOCAL_IN) |
			(1 << NF_INET_FORWARD);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return nft_chain_validate_hooks(ctx->chain, hooks);
#else
	return 0;
#endif
}