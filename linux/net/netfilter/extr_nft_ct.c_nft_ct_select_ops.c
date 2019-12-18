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
 size_t NFTA_CT_DREG ; 
 size_t NFTA_CT_KEY ; 
 size_t NFTA_CT_SREG ; 
 int /*<<< orphan*/  NFT_CT_ZONE ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 struct nft_expr_ops const nft_ct_get_ops ; 
 struct nft_expr_ops const nft_ct_set_ops ; 
 struct nft_expr_ops const nft_ct_set_zone_ops ; 
 scalar_t__ nla_get_be32 (struct nlattr const* const) ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_ct_select_ops(const struct nft_ctx *ctx,
		    const struct nlattr * const tb[])
{
	if (tb[NFTA_CT_KEY] == NULL)
		return ERR_PTR(-EINVAL);

	if (tb[NFTA_CT_DREG] && tb[NFTA_CT_SREG])
		return ERR_PTR(-EINVAL);

	if (tb[NFTA_CT_DREG])
		return &nft_ct_get_ops;

	if (tb[NFTA_CT_SREG]) {
#ifdef CONFIG_NF_CONNTRACK_ZONES
		if (nla_get_be32(tb[NFTA_CT_KEY]) == htonl(NFT_CT_ZONE))
			return &nft_ct_set_zone_ops;
#endif
		return &nft_ct_set_ops;
	}

	return ERR_PTR(-EINVAL);
}