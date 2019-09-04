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
struct nft_range_expr {int /*<<< orphan*/  len; int /*<<< orphan*/  data_to; int /*<<< orphan*/  data_from; int /*<<< orphan*/  op; int /*<<< orphan*/  sreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_RANGE_FROM_DATA ; 
 int /*<<< orphan*/  NFTA_RANGE_OP ; 
 int /*<<< orphan*/  NFTA_RANGE_SREG ; 
 int /*<<< orphan*/  NFTA_RANGE_TO_DATA ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_data_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_range_expr* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_range_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_range_expr *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_RANGE_SREG, priv->sreg))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_RANGE_OP, htonl(priv->op)))
		goto nla_put_failure;

	if (nft_data_dump(skb, NFTA_RANGE_FROM_DATA, &priv->data_from,
			  NFT_DATA_VALUE, priv->len) < 0 ||
	    nft_data_dump(skb, NFTA_RANGE_TO_DATA, &priv->data_to,
			  NFT_DATA_VALUE, priv->len) < 0)
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}