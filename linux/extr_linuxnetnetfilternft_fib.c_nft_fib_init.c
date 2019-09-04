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
struct nft_fib {int flags; int result; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IFNAMSIZ ; 
 size_t NFTA_FIB_DREG ; 
 size_t NFTA_FIB_FLAGS ; 
 int NFTA_FIB_F_ALL ; 
 int NFTA_FIB_F_DADDR ; 
 int NFTA_FIB_F_IIF ; 
 int NFTA_FIB_F_OIF ; 
 int NFTA_FIB_F_SADDR ; 
 size_t NFTA_FIB_RESULT ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
#define  NFT_FIB_RESULT_ADDRTYPE 130 
#define  NFT_FIB_RESULT_OIF 129 
#define  NFT_FIB_RESULT_OIFNAME 128 
 struct nft_fib* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

int nft_fib_init(const struct nft_ctx *ctx, const struct nft_expr *expr,
		 const struct nlattr * const tb[])
{
	struct nft_fib *priv = nft_expr_priv(expr);
	unsigned int len;
	int err;

	if (!tb[NFTA_FIB_DREG] || !tb[NFTA_FIB_RESULT] || !tb[NFTA_FIB_FLAGS])
		return -EINVAL;

	priv->flags = ntohl(nla_get_be32(tb[NFTA_FIB_FLAGS]));

	if (priv->flags == 0 || (priv->flags & ~NFTA_FIB_F_ALL))
		return -EINVAL;

	if ((priv->flags & (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR)) ==
			   (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR))
		return -EINVAL;
	if ((priv->flags & (NFTA_FIB_F_IIF | NFTA_FIB_F_OIF)) ==
			   (NFTA_FIB_F_IIF | NFTA_FIB_F_OIF))
		return -EINVAL;
	if ((priv->flags & (NFTA_FIB_F_SADDR | NFTA_FIB_F_DADDR)) == 0)
		return -EINVAL;

	priv->result = ntohl(nla_get_be32(tb[NFTA_FIB_RESULT]));
	priv->dreg = nft_parse_register(tb[NFTA_FIB_DREG]);

	switch (priv->result) {
	case NFT_FIB_RESULT_OIF:
		if (priv->flags & NFTA_FIB_F_OIF)
			return -EINVAL;
		len = sizeof(int);
		break;
	case NFT_FIB_RESULT_OIFNAME:
		if (priv->flags & NFTA_FIB_F_OIF)
			return -EINVAL;
		len = IFNAMSIZ;
		break;
	case NFT_FIB_RESULT_ADDRTYPE:
		len = sizeof(u32);
		break;
	default:
		return -EINVAL;
	}

	err = nft_validate_register_store(ctx, priv->dreg, NULL,
					  NFT_DATA_VALUE, len);
	if (err < 0)
		return err;

	return 0;
}