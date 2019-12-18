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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct nft_meta {int key; int /*<<< orphan*/  sreg; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NFTA_META_KEY ; 
 size_t NFTA_META_SREG ; 
#define  NFT_META_MARK 132 
#define  NFT_META_NFTRACE 131 
#define  NFT_META_PKTTYPE 130 
#define  NFT_META_PRIORITY 129 
#define  NFT_META_SECMARK 128 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int /*<<< orphan*/  nft_trace_enabled ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_branch_inc (int /*<<< orphan*/ *) ; 

int nft_meta_set_init(const struct nft_ctx *ctx,
		      const struct nft_expr *expr,
		      const struct nlattr * const tb[])
{
	struct nft_meta *priv = nft_expr_priv(expr);
	unsigned int len;
	int err;

	priv->key = ntohl(nla_get_be32(tb[NFTA_META_KEY]));
	switch (priv->key) {
	case NFT_META_MARK:
	case NFT_META_PRIORITY:
#ifdef CONFIG_NETWORK_SECMARK
	case NFT_META_SECMARK:
#endif
		len = sizeof(u32);
		break;
	case NFT_META_NFTRACE:
		len = sizeof(u8);
		break;
	case NFT_META_PKTTYPE:
		len = sizeof(u8);
		break;
	default:
		return -EOPNOTSUPP;
	}

	priv->sreg = nft_parse_register(tb[NFTA_META_SREG]);
	err = nft_validate_register_load(priv->sreg, len);
	if (err < 0)
		return err;

	if (priv->key == NFT_META_NFTRACE)
		static_branch_inc(&nft_trace_enabled);

	return 0;
}