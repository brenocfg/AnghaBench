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
struct nft_fwd_neigh {int /*<<< orphan*/  nfproto; int /*<<< orphan*/  sreg_addr; int /*<<< orphan*/  sreg_dev; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_FWD_NFPROTO ; 
 int /*<<< orphan*/  NFTA_FWD_SREG_ADDR ; 
 int /*<<< orphan*/  NFTA_FWD_SREG_DEV ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_fwd_neigh* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_fwd_neigh_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	struct nft_fwd_neigh *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_FWD_SREG_DEV, priv->sreg_dev) ||
	    nft_dump_register(skb, NFTA_FWD_SREG_ADDR, priv->sreg_addr) ||
	    nla_put_be32(skb, NFTA_FWD_NFPROTO, htonl(priv->nfproto)))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}