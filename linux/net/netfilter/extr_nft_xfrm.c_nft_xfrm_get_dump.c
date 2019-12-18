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
struct nft_xfrm {int /*<<< orphan*/  spnum; int /*<<< orphan*/  dir; int /*<<< orphan*/  key; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_XFRM_DIR ; 
 int /*<<< orphan*/  NFTA_XFRM_DREG ; 
 int /*<<< orphan*/  NFTA_XFRM_KEY ; 
 int /*<<< orphan*/  NFTA_XFRM_SPNUM ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_xfrm* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_xfrm_get_dump(struct sk_buff *skb,
			     const struct nft_expr *expr)
{
	const struct nft_xfrm *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_XFRM_DREG, priv->dreg))
		return -1;

	if (nla_put_be32(skb, NFTA_XFRM_KEY, htonl(priv->key)))
		return -1;
	if (nla_put_u8(skb, NFTA_XFRM_DIR, priv->dir))
		return -1;
	if (nla_put_be32(skb, NFTA_XFRM_SPNUM, htonl(priv->spnum)))
		return -1;

	return 0;
}