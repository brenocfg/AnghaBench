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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nft_symhash {size_t dreg; scalar_t__ offset; int /*<<< orphan*/  modulus; } ;
struct nft_regs {scalar_t__* data; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_get_hash_symmetric (struct sk_buff*) ; 
 struct nft_symhash* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_symhash_eval(const struct nft_expr *expr,
			     struct nft_regs *regs,
			     const struct nft_pktinfo *pkt)
{
	struct nft_symhash *priv = nft_expr_priv(expr);
	struct sk_buff *skb = pkt->skb;
	u32 h;

	h = reciprocal_scale(__skb_get_hash_symmetric(skb), priv->modulus);

	regs->data[priv->dreg] = h + priv->offset;
}