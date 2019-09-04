#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nft_lookup {int /*<<< orphan*/  dreg; TYPE_1__* set; int /*<<< orphan*/  sreg; scalar_t__ invert; } ;
struct nft_expr {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_LOOKUP_DREG ; 
 int /*<<< orphan*/  NFTA_LOOKUP_FLAGS ; 
 int /*<<< orphan*/  NFTA_LOOKUP_SET ; 
 int /*<<< orphan*/  NFTA_LOOKUP_SREG ; 
 int /*<<< orphan*/  NFT_LOOKUP_F_INV ; 
 int NFT_SET_MAP ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_lookup* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_lookup_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_lookup *priv = nft_expr_priv(expr);
	u32 flags = priv->invert ? NFT_LOOKUP_F_INV : 0;

	if (nla_put_string(skb, NFTA_LOOKUP_SET, priv->set->name))
		goto nla_put_failure;
	if (nft_dump_register(skb, NFTA_LOOKUP_SREG, priv->sreg))
		goto nla_put_failure;
	if (priv->set->flags & NFT_SET_MAP)
		if (nft_dump_register(skb, NFTA_LOOKUP_DREG, priv->dreg))
			goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_LOOKUP_FLAGS, htonl(flags)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}