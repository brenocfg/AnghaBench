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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct nft_tunnel {int key; scalar_t__ mode; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NFTA_TUNNEL_DREG ; 
 size_t NFTA_TUNNEL_KEY ; 
 size_t NFTA_TUNNEL_MODE ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
#define  NFT_TUNNEL_ID 129 
 scalar_t__ NFT_TUNNEL_MODE_MAX ; 
 scalar_t__ NFT_TUNNEL_MODE_NONE ; 
#define  NFT_TUNNEL_PATH 128 
 struct nft_tunnel* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_tunnel_get_init(const struct nft_ctx *ctx,
			       const struct nft_expr *expr,
			       const struct nlattr * const tb[])
{
	struct nft_tunnel *priv = nft_expr_priv(expr);
	u32 len;

	if (!tb[NFTA_TUNNEL_KEY] &&
	    !tb[NFTA_TUNNEL_DREG])
		return -EINVAL;

	priv->key = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY]));
	switch (priv->key) {
	case NFT_TUNNEL_PATH:
		len = sizeof(u8);
		break;
	case NFT_TUNNEL_ID:
		len = sizeof(u32);
		break;
	default:
		return -EOPNOTSUPP;
	}

	priv->dreg = nft_parse_register(tb[NFTA_TUNNEL_DREG]);

	if (tb[NFTA_TUNNEL_MODE]) {
		priv->mode = ntohl(nla_get_be32(tb[NFTA_TUNNEL_MODE]));
		if (priv->mode > NFT_TUNNEL_MODE_MAX)
			return -EOPNOTSUPP;
	} else {
		priv->mode = NFT_TUNNEL_MODE_NONE;
	}

	return nft_validate_register_store(ctx, priv->dreg, NULL,
					   NFT_DATA_VALUE, len);
}