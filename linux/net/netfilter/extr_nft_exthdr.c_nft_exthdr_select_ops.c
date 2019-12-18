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
struct nft_ctx {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 size_t NFTA_EXTHDR_DREG ; 
 size_t NFTA_EXTHDR_OP ; 
 size_t NFTA_EXTHDR_SREG ; 
#define  NFT_EXTHDR_OP_IPV4 130 
#define  NFT_EXTHDR_OP_IPV6 129 
#define  NFT_EXTHDR_OP_TCPOPT 128 
 struct nft_expr_ops const nft_exthdr_ipv4_ops ; 
 struct nft_expr_ops const nft_exthdr_ipv6_ops ; 
 struct nft_expr_ops const nft_exthdr_tcp_ops ; 
 struct nft_expr_ops const nft_exthdr_tcp_set_ops ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_exthdr_select_ops(const struct nft_ctx *ctx,
		      const struct nlattr * const tb[])
{
	u32 op;

	if (!tb[NFTA_EXTHDR_OP])
		return &nft_exthdr_ipv6_ops;

	if (tb[NFTA_EXTHDR_SREG] && tb[NFTA_EXTHDR_DREG])
		return ERR_PTR(-EOPNOTSUPP);

	op = ntohl(nla_get_be32(tb[NFTA_EXTHDR_OP]));
	switch (op) {
	case NFT_EXTHDR_OP_TCPOPT:
		if (tb[NFTA_EXTHDR_SREG])
			return &nft_exthdr_tcp_set_ops;
		if (tb[NFTA_EXTHDR_DREG])
			return &nft_exthdr_tcp_ops;
		break;
	case NFT_EXTHDR_OP_IPV6:
		if (tb[NFTA_EXTHDR_DREG])
			return &nft_exthdr_ipv6_ops;
		break;
	case NFT_EXTHDR_OP_IPV4:
		if (ctx->family != NFPROTO_IPV6) {
			if (tb[NFTA_EXTHDR_DREG])
				return &nft_exthdr_ipv4_ops;
		}
		break;
	}

	return ERR_PTR(-EOPNOTSUPP);
}