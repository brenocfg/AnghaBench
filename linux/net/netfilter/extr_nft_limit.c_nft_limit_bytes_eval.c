#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_2__ verdict; } ;
struct nft_pktinfo {TYPE_1__* skb; } ;
struct nft_limit {int nsecs; int /*<<< orphan*/  rate; } ;
struct nft_expr {int dummy; } ;
struct TYPE_3__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  div64_u64 (int,int /*<<< orphan*/ ) ; 
 struct nft_limit* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_limit_eval (struct nft_limit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_limit_bytes_eval(const struct nft_expr *expr,
				 struct nft_regs *regs,
				 const struct nft_pktinfo *pkt)
{
	struct nft_limit *priv = nft_expr_priv(expr);
	u64 cost = div64_u64(priv->nsecs * pkt->skb->len, priv->rate);

	if (nft_limit_eval(priv, cost))
		regs->verdict.code = NFT_BREAK;
}