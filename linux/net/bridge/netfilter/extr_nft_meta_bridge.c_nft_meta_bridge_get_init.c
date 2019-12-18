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
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct nft_meta {int key; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 unsigned int IFNAMSIZ ; 
 size_t NFTA_META_DREG ; 
 size_t NFTA_META_KEY ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
#define  NFT_META_BRI_IIFNAME 131 
#define  NFT_META_BRI_IIFPVID 130 
#define  NFT_META_BRI_IIFVPROTO 129 
#define  NFT_META_BRI_OIFNAME 128 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 
 int nft_meta_get_init (struct nft_ctx const*,struct nft_expr const*,struct nlattr const* const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_meta_bridge_get_init(const struct nft_ctx *ctx,
				    const struct nft_expr *expr,
				    const struct nlattr * const tb[])
{
	struct nft_meta *priv = nft_expr_priv(expr);
	unsigned int len;

	priv->key = ntohl(nla_get_be32(tb[NFTA_META_KEY]));
	switch (priv->key) {
	case NFT_META_BRI_IIFNAME:
	case NFT_META_BRI_OIFNAME:
		len = IFNAMSIZ;
		break;
	case NFT_META_BRI_IIFPVID:
	case NFT_META_BRI_IIFVPROTO:
		len = sizeof(u16);
		break;
	default:
		return nft_meta_get_init(ctx, expr, tb);
	}

	priv->dreg = nft_parse_register(tb[NFTA_META_DREG]);
	return nft_validate_register_store(ctx, priv->dreg, NULL,
					   NFT_DATA_VALUE, len);
}