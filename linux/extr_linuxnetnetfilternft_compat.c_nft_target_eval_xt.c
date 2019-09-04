#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_target {int (* target ) (struct sk_buff*,TYPE_3__*) ;} ;
struct xt_action_param {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct TYPE_6__ {scalar_t__ hotdrop; } ;
struct nft_pktinfo {TYPE_3__ xt; struct sk_buff* skb; } ;
struct nft_expr {TYPE_2__* ops; } ;
struct TYPE_5__ {struct xt_target* data; } ;

/* Variables and functions */
 int NFT_CONTINUE ; 
 int /*<<< orphan*/  NF_DROP ; 
#define  XT_CONTINUE 128 
 int /*<<< orphan*/  nft_compat_set_par (struct xt_action_param*,struct xt_target*,void*) ; 
 void* nft_expr_priv (struct nft_expr const*) ; 
 int stub1 (struct sk_buff*,TYPE_3__*) ; 

__attribute__((used)) static void nft_target_eval_xt(const struct nft_expr *expr,
			       struct nft_regs *regs,
			       const struct nft_pktinfo *pkt)
{
	void *info = nft_expr_priv(expr);
	struct xt_target *target = expr->ops->data;
	struct sk_buff *skb = pkt->skb;
	int ret;

	nft_compat_set_par((struct xt_action_param *)&pkt->xt, target, info);

	ret = target->target(skb, &pkt->xt);

	if (pkt->xt.hotdrop)
		ret = NF_DROP;

	switch (ret) {
	case XT_CONTINUE:
		regs->verdict.code = NFT_CONTINUE;
		break;
	default:
		regs->verdict.code = ret;
		break;
	}
}