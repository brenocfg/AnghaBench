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
struct nft_dup_ipv6 {scalar_t__ sreg_dev; scalar_t__ sreg_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFTA_DUP_SREG_ADDR ; 
 int /*<<< orphan*/  NFTA_DUP_SREG_DEV ; 
 scalar_t__ nft_dump_register (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct nft_dup_ipv6* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_dup_ipv6_dump(struct sk_buff *skb, const struct nft_expr *expr)
{
	struct nft_dup_ipv6 *priv = nft_expr_priv(expr);

	if (nft_dump_register(skb, NFTA_DUP_SREG_ADDR, priv->sreg_addr))
		goto nla_put_failure;
	if (priv->sreg_dev &&
	    nft_dump_register(skb, NFTA_DUP_SREG_DEV, priv->sreg_dev))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}