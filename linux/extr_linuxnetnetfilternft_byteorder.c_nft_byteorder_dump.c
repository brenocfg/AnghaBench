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
struct nft_byteorder {int /*<<< orphan*/  size; int /*<<< orphan*/  len; int /*<<< orphan*/  op; int /*<<< orphan*/  dreg; int /*<<< orphan*/  sreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_BYTEORDER_DREG ; 
 int /*<<< orphan*/  NFTA_BYTEORDER_LEN ; 
 int /*<<< orphan*/  NFTA_BYTEORDER_OP ; 
 int /*<<< orphan*/  NFTA_BYTEORDER_SIZE ; 
 int /*<<< orphan*/  NFTA_BYTEORDER_SREG ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_byteorder* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_byteorder_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_byteorder *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_BYTEORDER_SREG, priv->sreg))
		goto nla_put_failure;
	if (nft_dump_register(skb, NFTA_BYTEORDER_DREG, priv->dreg))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_BYTEORDER_OP, htonl(priv->op)))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_BYTEORDER_LEN, htonl(priv->len)))
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_BYTEORDER_SIZE, htonl(priv->size)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}