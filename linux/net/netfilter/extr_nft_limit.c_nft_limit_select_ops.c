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
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t NFTA_LIMIT_TYPE ; 
#define  NFT_LIMIT_PKTS 129 
#define  NFT_LIMIT_PKT_BYTES 128 
 struct nft_expr_ops const nft_limit_bytes_ops ; 
 struct nft_expr_ops const nft_limit_pkts_ops ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_limit_select_ops(const struct nft_ctx *ctx,
		     const struct nlattr * const tb[])
{
	if (tb[NFTA_LIMIT_TYPE] == NULL)
		return &nft_limit_pkts_ops;

	switch (ntohl(nla_get_be32(tb[NFTA_LIMIT_TYPE]))) {
	case NFT_LIMIT_PKTS:
		return &nft_limit_pkts_ops;
	case NFT_LIMIT_PKT_BYTES:
		return &nft_limit_bytes_ops;
	}
	return ERR_PTR(-EOPNOTSUPP);
}