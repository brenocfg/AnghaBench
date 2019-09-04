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
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct nft_ng_inc {int offset; int modulus; int /*<<< orphan*/  dreg; int /*<<< orphan*/  counter; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int ERANGE ; 
 size_t NFTA_NG_DREG ; 
 size_t NFTA_NG_MODULUS ; 
 size_t NFTA_NG_OFFSET ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct nft_ng_inc* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_ng_inc_init(const struct nft_ctx *ctx,
			   const struct nft_expr *expr,
			   const struct nlattr * const tb[])
{
	struct nft_ng_inc *priv = nft_expr_priv(expr);

	if (tb[NFTA_NG_OFFSET])
		priv->offset = ntohl(nla_get_be32(tb[NFTA_NG_OFFSET]));

	priv->modulus = ntohl(nla_get_be32(tb[NFTA_NG_MODULUS]));
	if (priv->modulus == 0)
		return -ERANGE;

	if (priv->offset + priv->modulus - 1 < priv->offset)
		return -EOVERFLOW;

	priv->dreg = nft_parse_register(tb[NFTA_NG_DREG]);
	atomic_set(&priv->counter, priv->modulus - 1);

	return nft_validate_register_store(ctx, priv->dreg, NULL,
					   NFT_DATA_VALUE, sizeof(u32));
}