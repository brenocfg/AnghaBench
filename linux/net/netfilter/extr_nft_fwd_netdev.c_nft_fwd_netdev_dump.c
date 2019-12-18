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
struct nft_fwd_netdev {int /*<<< orphan*/  sreg_dev; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_FWD_SREG_DEV ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_fwd_netdev* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_fwd_netdev_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	struct nft_fwd_netdev *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_FWD_SREG_DEV, priv->sreg_dev))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}