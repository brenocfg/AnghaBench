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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct nft_xfrm {int key; int dir; int /*<<< orphan*/  dreg; scalar_t__ spnum; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int family; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
#define  NFPROTO_INET 138 
#define  NFPROTO_IPV4 137 
#define  NFPROTO_IPV6 136 
 size_t NFTA_XFRM_DIR ; 
 size_t NFTA_XFRM_DREG ; 
 size_t NFTA_XFRM_KEY ; 
 size_t NFTA_XFRM_SPNUM ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
#define  NFT_XFRM_KEY_DADDR_IP4 135 
#define  NFT_XFRM_KEY_DADDR_IP6 134 
#define  NFT_XFRM_KEY_REQID 133 
#define  NFT_XFRM_KEY_SADDR_IP4 132 
#define  NFT_XFRM_KEY_SADDR_IP6 131 
#define  NFT_XFRM_KEY_SPI 130 
 scalar_t__ XFRM_MAX_DEPTH ; 
#define  XFRM_POLICY_IN 129 
#define  XFRM_POLICY_OUT 128 
 struct nft_xfrm* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr const* const) ; 
 int nla_get_u8 (struct nlattr const* const) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_xfrm_get_init(const struct nft_ctx *ctx,
			     const struct nft_expr *expr,
			     const struct nlattr * const tb[])
{
	struct nft_xfrm *priv = nft_expr_priv(expr);
	unsigned int len = 0;
	u32 spnum = 0;
	u8 dir;

	if (!tb[NFTA_XFRM_KEY] || !tb[NFTA_XFRM_DIR] || !tb[NFTA_XFRM_DREG])
		return -EINVAL;

	switch (ctx->family) {
	case NFPROTO_IPV4:
	case NFPROTO_IPV6:
	case NFPROTO_INET:
		break;
	default:
		return -EOPNOTSUPP;
	}

	priv->key = ntohl(nla_get_u32(tb[NFTA_XFRM_KEY]));
	switch (priv->key) {
	case NFT_XFRM_KEY_REQID:
	case NFT_XFRM_KEY_SPI:
		len = sizeof(u32);
		break;
	case NFT_XFRM_KEY_DADDR_IP4:
	case NFT_XFRM_KEY_SADDR_IP4:
		len = sizeof(struct in_addr);
		break;
	case NFT_XFRM_KEY_DADDR_IP6:
	case NFT_XFRM_KEY_SADDR_IP6:
		len = sizeof(struct in6_addr);
		break;
	default:
		return -EINVAL;
	}

	dir = nla_get_u8(tb[NFTA_XFRM_DIR]);
	switch (dir) {
	case XFRM_POLICY_IN:
	case XFRM_POLICY_OUT:
		priv->dir = dir;
		break;
	default:
		return -EINVAL;
	}

	if (tb[NFTA_XFRM_SPNUM])
		spnum = ntohl(nla_get_be32(tb[NFTA_XFRM_SPNUM]));

	if (spnum >= XFRM_MAX_DEPTH)
		return -ERANGE;

	priv->spnum = spnum;

	priv->dreg = nft_parse_register(tb[NFTA_XFRM_DREG]);
	return nft_validate_register_store(ctx, priv->dreg, NULL,
					   NFT_DATA_VALUE, len);
}