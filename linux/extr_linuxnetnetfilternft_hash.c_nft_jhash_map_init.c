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
struct nlattr {int dummy; } ;
struct nft_jhash {int /*<<< orphan*/  map; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  table; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 size_t NFTA_HASH_SET_ID ; 
 size_t NFTA_HASH_SET_NAME ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 struct nft_jhash* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_genmask_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_jhash_init (struct nft_ctx const*,struct nft_expr const*,struct nlattr const* const*) ; 
 int /*<<< orphan*/  nft_set_lookup_global (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr const* const,struct nlattr const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_jhash_map_init(const struct nft_ctx *ctx,
			      const struct nft_expr *expr,
			      const struct nlattr * const tb[])
{
	struct nft_jhash *priv = nft_expr_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);

	nft_jhash_init(ctx, expr, tb);
	priv->map = nft_set_lookup_global(ctx->net, ctx->table,
					  tb[NFTA_HASH_SET_NAME],
					  tb[NFTA_HASH_SET_ID], genmask);
	return PTR_ERR_OR_ZERO(priv->map);
}