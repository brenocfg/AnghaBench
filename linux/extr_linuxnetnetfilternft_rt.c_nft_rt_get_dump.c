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
struct nft_rt {int /*<<< orphan*/  dreg; int /*<<< orphan*/  key; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_RT_DREG ; 
 int /*<<< orphan*/  NFTA_RT_KEY ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_rt* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_rt_get_dump(struct sk_buff *skb,
			   const struct nft_expr *expr)
{
	const struct nft_rt *priv = nft_expr_priv(expr);

	if (nla_put_be32(skb, NFTA_RT_KEY, htonl(priv->key)))
		goto nla_put_failure;
	if (nft_dump_register(skb, NFTA_RT_DREG, priv->dreg))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}