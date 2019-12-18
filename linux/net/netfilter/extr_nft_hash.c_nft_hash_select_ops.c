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
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct nft_expr_ops {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t NFTA_HASH_TYPE ; 
#define  NFT_HASH_JENKINS 129 
#define  NFT_HASH_SYM 128 
 struct nft_expr_ops const nft_jhash_ops ; 
 struct nft_expr_ops const nft_symhash_ops ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_hash_select_ops(const struct nft_ctx *ctx,
		    const struct nlattr * const tb[])
{
	u32 type;

	if (!tb[NFTA_HASH_TYPE])
		return &nft_jhash_ops;

	type = ntohl(nla_get_be32(tb[NFTA_HASH_TYPE]));
	switch (type) {
	case NFT_HASH_SYM:
		return &nft_symhash_ops;
	case NFT_HASH_JENKINS:
		return &nft_jhash_ops;
	default:
		break;
	}
	return ERR_PTR(-EOPNOTSUPP);
}