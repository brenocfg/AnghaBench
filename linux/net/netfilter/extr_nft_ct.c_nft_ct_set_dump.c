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
struct sk_buff {int dummy; } ;
struct nft_expr {int dummy; } ;
struct nft_ct {int key; int /*<<< orphan*/  dir; int /*<<< orphan*/  sreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_DIR_MAX ; 
 int /*<<< orphan*/  NFTA_CT_DIRECTION ; 
 int /*<<< orphan*/  NFTA_CT_KEY ; 
 int /*<<< orphan*/  NFTA_CT_SREG ; 
#define  NFT_CT_ZONE 128 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_ct* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_ct_set_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_ct *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_CT_SREG, priv->sreg))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_CT_KEY, htonl(priv->key)))
		goto nla_put_failure;

	switch (priv->key) {
	case NFT_CT_ZONE:
		if (priv->dir < IP_CT_DIR_MAX &&
		    nla_put_u8(skb, NFTA_CT_DIRECTION, priv->dir))
			goto nla_put_failure;
		break;
	default:
		break;
	}

	return 0;

nla_put_failure:
	return -1;
}