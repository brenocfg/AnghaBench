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
typedef  enum nft_fib_result { ____Placeholder_nft_fib_result } nft_fib_result ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t NFTA_FIB_RESULT ; 
#define  NFT_FIB_RESULT_ADDRTYPE 130 
#define  NFT_FIB_RESULT_OIF 129 
#define  NFT_FIB_RESULT_OIFNAME 128 
 struct nft_expr_ops const nft_fib6_ops ; 
 struct nft_expr_ops const nft_fib6_type_ops ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_fib6_select_ops(const struct nft_ctx *ctx,
		    const struct nlattr * const tb[])
{
	enum nft_fib_result result;

	if (!tb[NFTA_FIB_RESULT])
		return ERR_PTR(-EINVAL);

	result = ntohl(nla_get_be32(tb[NFTA_FIB_RESULT]));

	switch (result) {
	case NFT_FIB_RESULT_OIF:
		return &nft_fib6_ops;
	case NFT_FIB_RESULT_OIFNAME:
		return &nft_fib6_ops;
	case NFT_FIB_RESULT_ADDRTYPE:
		return &nft_fib6_type_ops;
	default:
		return ERR_PTR(-EOPNOTSUPP);
	}
}