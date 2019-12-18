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
struct nft_fib {int /*<<< orphan*/  flags; int /*<<< orphan*/  result; int /*<<< orphan*/  dreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_FIB_DREG ; 
 int /*<<< orphan*/  NFTA_FIB_FLAGS ; 
 int /*<<< orphan*/  NFTA_FIB_RESULT ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_fib* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nft_fib_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	const struct nft_fib *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_FIB_DREG, priv->dreg))
		return -1;

	if (nla_put_be32(skb, NFTA_FIB_RESULT, htonl(priv->result)))
		return -1;

	if (nla_put_be32(skb, NFTA_FIB_FLAGS, htonl(priv->flags)))
		return -1;

	return 0;
}