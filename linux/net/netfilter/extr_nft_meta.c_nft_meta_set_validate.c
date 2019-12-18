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
struct nft_meta {scalar_t__ key; } ;
struct nft_expr {int dummy; } ;
struct nft_data {int dummy; } ;
struct nft_ctx {int family; int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NFPROTO_BRIDGE 132 
#define  NFPROTO_INET 131 
#define  NFPROTO_IPV4 130 
#define  NFPROTO_IPV6 129 
#define  NFPROTO_NETDEV 128 
 scalar_t__ NFT_META_PKTTYPE ; 
 int NF_BR_PRE_ROUTING ; 
 int NF_INET_PRE_ROUTING ; 
 int NF_NETDEV_INGRESS ; 
 int nft_chain_validate_hooks (int /*<<< orphan*/ ,unsigned int) ; 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 

int nft_meta_set_validate(const struct nft_ctx *ctx,
			  const struct nft_expr *expr,
			  const struct nft_data **data)
{
	struct nft_meta *priv = nft_expr_priv(expr);
	unsigned int hooks;

	if (priv->key != NFT_META_PKTTYPE)
		return 0;

	switch (ctx->family) {
	case NFPROTO_BRIDGE:
		hooks = 1 << NF_BR_PRE_ROUTING;
		break;
	case NFPROTO_NETDEV:
		hooks = 1 << NF_NETDEV_INGRESS;
		break;
	case NFPROTO_IPV4:
	case NFPROTO_IPV6:
	case NFPROTO_INET:
		hooks = 1 << NF_INET_PRE_ROUTING;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return nft_chain_validate_hooks(ctx->chain, hooks);
}