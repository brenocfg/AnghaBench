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
typedef  void* u32 ;
struct nlattr {int dummy; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;
struct nft_byteorder {int op; int size; void* len; void* dreg; void* sreg; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_BYTEORDER_DREG ; 
 size_t NFTA_BYTEORDER_LEN ; 
 size_t NFTA_BYTEORDER_OP ; 
 size_t NFTA_BYTEORDER_SIZE ; 
 size_t NFTA_BYTEORDER_SREG ; 
#define  NFT_BYTEORDER_HTON 129 
#define  NFT_BYTEORDER_NTOH 128 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
 int /*<<< orphan*/  U8_MAX ; 
 struct nft_byteorder* nft_expr_priv (struct nft_expr const*) ; 
 void* nft_parse_register (struct nlattr const* const) ; 
 int nft_parse_u32_check (struct nlattr const* const,int /*<<< orphan*/ ,void**) ; 
 int nft_validate_register_load (void*,void*) ; 
 int nft_validate_register_store (struct nft_ctx const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_byteorder_init(const struct nft_ctx *ctx,
			      const struct nft_expr *expr,
			      const struct nlattr * const tb[])
{
	struct nft_byteorder *priv = nft_expr_priv(expr);
	u32 size, len;
	int err;

	if (tb[NFTA_BYTEORDER_SREG] == NULL ||
	    tb[NFTA_BYTEORDER_DREG] == NULL ||
	    tb[NFTA_BYTEORDER_LEN] == NULL ||
	    tb[NFTA_BYTEORDER_SIZE] == NULL ||
	    tb[NFTA_BYTEORDER_OP] == NULL)
		return -EINVAL;

	priv->op = ntohl(nla_get_be32(tb[NFTA_BYTEORDER_OP]));
	switch (priv->op) {
	case NFT_BYTEORDER_NTOH:
	case NFT_BYTEORDER_HTON:
		break;
	default:
		return -EINVAL;
	}

	err = nft_parse_u32_check(tb[NFTA_BYTEORDER_SIZE], U8_MAX, &size);
	if (err < 0)
		return err;

	priv->size = size;

	switch (priv->size) {
	case 2:
	case 4:
	case 8:
		break;
	default:
		return -EINVAL;
	}

	priv->sreg = nft_parse_register(tb[NFTA_BYTEORDER_SREG]);
	err = nft_parse_u32_check(tb[NFTA_BYTEORDER_LEN], U8_MAX, &len);
	if (err < 0)
		return err;

	priv->len = len;

	err = nft_validate_register_load(priv->sreg, priv->len);
	if (err < 0)
		return err;

	priv->dreg = nft_parse_register(tb[NFTA_BYTEORDER_DREG]);
	return nft_validate_register_store(ctx, priv->dreg, NULL,
					   NFT_DATA_VALUE, priv->len);
}