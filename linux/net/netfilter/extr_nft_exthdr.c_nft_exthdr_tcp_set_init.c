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
struct nft_exthdr {int offset; int len; int flags; int op; int /*<<< orphan*/  sreg; int /*<<< orphan*/  type; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NFTA_EXTHDR_DREG ; 
 size_t NFTA_EXTHDR_FLAGS ; 
 size_t NFTA_EXTHDR_LEN ; 
 size_t NFTA_EXTHDR_OFFSET ; 
 size_t NFTA_EXTHDR_OP ; 
 size_t NFTA_EXTHDR_SREG ; 
 size_t NFTA_EXTHDR_TYPE ; 
 int NFT_EXTHDR_OP_IPV6 ; 
 int /*<<< orphan*/  U8_MAX ; 
 struct nft_exthdr* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_parse_u32_check (struct nlattr const* const,int /*<<< orphan*/ ,int*) ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr const* const) ; 

__attribute__((used)) static int nft_exthdr_tcp_set_init(const struct nft_ctx *ctx,
				   const struct nft_expr *expr,
				   const struct nlattr * const tb[])
{
	struct nft_exthdr *priv = nft_expr_priv(expr);
	u32 offset, len, flags = 0, op = NFT_EXTHDR_OP_IPV6;
	int err;

	if (!tb[NFTA_EXTHDR_SREG] ||
	    !tb[NFTA_EXTHDR_TYPE] ||
	    !tb[NFTA_EXTHDR_OFFSET] ||
	    !tb[NFTA_EXTHDR_LEN])
		return -EINVAL;

	if (tb[NFTA_EXTHDR_DREG] || tb[NFTA_EXTHDR_FLAGS])
		return -EINVAL;

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_OFFSET], U8_MAX, &offset);
	if (err < 0)
		return err;

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_LEN], U8_MAX, &len);
	if (err < 0)
		return err;

	if (offset < 2)
		return -EOPNOTSUPP;

	switch (len) {
	case 2: break;
	case 4: break;
	default:
		return -EOPNOTSUPP;
	}

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_OP], U8_MAX, &op);
	if (err < 0)
		return err;

	priv->type   = nla_get_u8(tb[NFTA_EXTHDR_TYPE]);
	priv->offset = offset;
	priv->len    = len;
	priv->sreg   = nft_parse_register(tb[NFTA_EXTHDR_SREG]);
	priv->flags  = flags;
	priv->op     = op;

	return nft_validate_register_load(priv->sreg, priv->len);
}