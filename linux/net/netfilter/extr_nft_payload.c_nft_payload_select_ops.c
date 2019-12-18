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
typedef  enum nft_payload_bases { ____Placeholder_nft_payload_bases } nft_payload_bases ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ALIGNED (unsigned int,unsigned int) ; 
 size_t NFTA_PAYLOAD_BASE ; 
 size_t NFTA_PAYLOAD_DREG ; 
 size_t NFTA_PAYLOAD_LEN ; 
 size_t NFTA_PAYLOAD_OFFSET ; 
 size_t NFTA_PAYLOAD_SREG ; 
#define  NFT_PAYLOAD_LL_HEADER 130 
#define  NFT_PAYLOAD_NETWORK_HEADER 129 
#define  NFT_PAYLOAD_TRANSPORT_HEADER 128 
 scalar_t__ is_power_of_2 (unsigned int) ; 
 struct nft_expr_ops const nft_payload_fast_ops ; 
 struct nft_expr_ops const nft_payload_ops ; 
 struct nft_expr_ops const nft_payload_set_ops ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_payload_select_ops(const struct nft_ctx *ctx,
		       const struct nlattr * const tb[])
{
	enum nft_payload_bases base;
	unsigned int offset, len;

	if (tb[NFTA_PAYLOAD_BASE] == NULL ||
	    tb[NFTA_PAYLOAD_OFFSET] == NULL ||
	    tb[NFTA_PAYLOAD_LEN] == NULL)
		return ERR_PTR(-EINVAL);

	base = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_BASE]));
	switch (base) {
	case NFT_PAYLOAD_LL_HEADER:
	case NFT_PAYLOAD_NETWORK_HEADER:
	case NFT_PAYLOAD_TRANSPORT_HEADER:
		break;
	default:
		return ERR_PTR(-EOPNOTSUPP);
	}

	if (tb[NFTA_PAYLOAD_SREG] != NULL) {
		if (tb[NFTA_PAYLOAD_DREG] != NULL)
			return ERR_PTR(-EINVAL);
		return &nft_payload_set_ops;
	}

	if (tb[NFTA_PAYLOAD_DREG] == NULL)
		return ERR_PTR(-EINVAL);

	offset = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_OFFSET]));
	len    = ntohl(nla_get_be32(tb[NFTA_PAYLOAD_LEN]));

	if (len <= 4 && is_power_of_2(len) && IS_ALIGNED(offset, len) &&
	    base != NFT_PAYLOAD_LL_HEADER)
		return &nft_payload_fast_ops;
	else
		return &nft_payload_ops;
}