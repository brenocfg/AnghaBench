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
typedef  int /*<<< orphan*/  u16 ;
struct nlattr {int dummy; } ;
struct nft_meta {int key; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 unsigned int IFNAMSIZ ; 
 size_t NFTA_META_DREG ; 
 size_t NFTA_META_KEY ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
#define  NFT_META_CPU 146 
#define  NFT_META_IIF 145 
#define  NFT_META_IIFGROUP 144 
#define  NFT_META_IIFNAME 143 
#define  NFT_META_IIFTYPE 142 
#define  NFT_META_L4PROTO 141 
#define  NFT_META_LEN 140 
#define  NFT_META_MARK 139 
#define  NFT_META_NFPROTO 138 
#define  NFT_META_OIF 137 
#define  NFT_META_OIFGROUP 136 
#define  NFT_META_OIFNAME 135 
#define  NFT_META_OIFTYPE 134 
#define  NFT_META_PKTTYPE 133 
#define  NFT_META_PRANDOM 132 
#define  NFT_META_PRIORITY 131 
#define  NFT_META_PROTOCOL 130 
#define  NFT_META_SKGID 129 
#define  NFT_META_SKUID 128 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int /*<<< orphan*/  nft_prandom_state ; 
 int nft_validate_register_store (struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prandom_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nft_meta_get_init(const struct nft_ctx *ctx,
			     const struct nft_expr *expr,
			     const struct nlattr * const tb[])
{
	struct nft_meta *priv = nft_expr_priv(expr);
	unsigned int len;

	priv->key = ntohl(nla_get_be32(tb[NFTA_META_KEY]));
	switch (priv->key) {
	case NFT_META_PROTOCOL:
	case NFT_META_IIFTYPE:
	case NFT_META_OIFTYPE:
		len = sizeof(u16);
		break;
	case NFT_META_NFPROTO:
	case NFT_META_L4PROTO:
	case NFT_META_LEN:
	case NFT_META_PRIORITY:
	case NFT_META_MARK:
	case NFT_META_IIF:
	case NFT_META_OIF:
	case NFT_META_SKUID:
	case NFT_META_SKGID:
#ifdef CONFIG_IP_ROUTE_CLASSID
	case NFT_META_RTCLASSID:
#endif
#ifdef CONFIG_NETWORK_SECMARK
	case NFT_META_SECMARK:
#endif
	case NFT_META_PKTTYPE:
	case NFT_META_CPU:
	case NFT_META_IIFGROUP:
	case NFT_META_OIFGROUP:
#ifdef CONFIG_CGROUP_NET_CLASSID
	case NFT_META_CGROUP:
#endif
		len = sizeof(u32);
		break;
	case NFT_META_IIFNAME:
	case NFT_META_OIFNAME:
		len = IFNAMSIZ;
		break;
	case NFT_META_PRANDOM:
		prandom_init_once(&nft_prandom_state);
		len = sizeof(u32);
		break;
#ifdef CONFIG_XFRM
	case NFT_META_SECPATH:
		len = sizeof(u8);
		break;
#endif
#ifdef CONFIG_NF_TABLES_BRIDGE
	case NFT_META_BRI_IIFNAME:
	case NFT_META_BRI_OIFNAME:
		if (ctx->family != NFPROTO_BRIDGE)
			return -EOPNOTSUPP;
		len = IFNAMSIZ;
		break;
#endif
	default:
		return -EOPNOTSUPP;
	}

	priv->dreg = nft_parse_register(tb[NFTA_META_DREG]);
	return nft_validate_register_store(ctx, priv->dreg, NULL,
					   NFT_DATA_VALUE, len);
}