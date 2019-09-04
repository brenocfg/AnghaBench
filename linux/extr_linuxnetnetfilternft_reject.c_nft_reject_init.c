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
struct nft_reject {int type; int /*<<< orphan*/  icmp_code; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_REJECT_ICMP_CODE ; 
 size_t NFTA_REJECT_TYPE ; 
#define  NFT_REJECT_ICMP_UNREACH 129 
#define  NFT_REJECT_TCP_RST 128 
 struct nft_reject* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int nft_reject_init(const struct nft_ctx *ctx,
		    const struct nft_expr *expr,
		    const struct nlattr * const tb[])
{
	struct nft_reject *priv = nft_expr_priv(expr);

	if (tb[NFTA_REJECT_TYPE] == NULL)
		return -EINVAL;

	priv->type = ntohl(nla_get_be32(tb[NFTA_REJECT_TYPE]));
	switch (priv->type) {
	case NFT_REJECT_ICMP_UNREACH:
		if (tb[NFTA_REJECT_ICMP_CODE] == NULL)
			return -EINVAL;
		priv->icmp_code = nla_get_u8(tb[NFTA_REJECT_ICMP_CODE]);
	case NFT_REJECT_TCP_RST:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}