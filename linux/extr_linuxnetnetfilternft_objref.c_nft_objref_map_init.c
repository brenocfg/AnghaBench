#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct nft_set {int flags; int /*<<< orphan*/  klen; } ;
struct TYPE_2__ {int flags; } ;
struct nft_objref_map {struct nft_set* set; TYPE_1__ binding; int /*<<< orphan*/  sreg; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  table; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct nft_set*) ; 
 size_t NFTA_OBJREF_SET_ID ; 
 size_t NFTA_OBJREF_SET_NAME ; 
 size_t NFTA_OBJREF_SET_SREG ; 
 int NFT_SET_OBJECT ; 
 int PTR_ERR (struct nft_set*) ; 
 int nf_tables_bind_set (struct nft_ctx const*,struct nft_set*,TYPE_1__*) ; 
 struct nft_objref_map* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_genmask_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 struct nft_set* nft_set_lookup_global (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr const* const,struct nlattr const* const,int /*<<< orphan*/ ) ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_objref_map_init(const struct nft_ctx *ctx,
			       const struct nft_expr *expr,
			       const struct nlattr * const tb[])
{
	struct nft_objref_map *priv = nft_expr_priv(expr);
	u8 genmask = nft_genmask_next(ctx->net);
	struct nft_set *set;
	int err;

	set = nft_set_lookup_global(ctx->net, ctx->table,
				    tb[NFTA_OBJREF_SET_NAME],
				    tb[NFTA_OBJREF_SET_ID], genmask);
	if (IS_ERR(set))
		return PTR_ERR(set);

	if (!(set->flags & NFT_SET_OBJECT))
		return -EINVAL;

	priv->sreg = nft_parse_register(tb[NFTA_OBJREF_SET_SREG]);
	err = nft_validate_register_load(priv->sreg, set->klen);
	if (err < 0)
		return err;

	priv->binding.flags = set->flags & NFT_SET_OBJECT;

	err = nf_tables_bind_set(ctx, set, &priv->binding);
	if (err < 0)
		return err;

	priv->set = set;
	return 0;
}