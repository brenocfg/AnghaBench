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
struct nft_expr_ops {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t NFTA_META_DREG ; 
 size_t NFTA_META_KEY ; 
 size_t NFTA_META_SREG ; 
 struct nft_expr_ops const nft_meta_bridge_get_ops ; 
 struct nft_expr_ops const nft_meta_bridge_set_ops ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_meta_bridge_select_ops(const struct nft_ctx *ctx,
			   const struct nlattr * const tb[])
{
	if (tb[NFTA_META_KEY] == NULL)
		return ERR_PTR(-EINVAL);

	if (tb[NFTA_META_DREG] && tb[NFTA_META_SREG])
		return ERR_PTR(-EINVAL);

	if (tb[NFTA_META_DREG])
		return &nft_meta_bridge_get_ops;

	if (tb[NFTA_META_SREG])
		return &nft_meta_bridge_set_ops;

	return ERR_PTR(-EINVAL);
}