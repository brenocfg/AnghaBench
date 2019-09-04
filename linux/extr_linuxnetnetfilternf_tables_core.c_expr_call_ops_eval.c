#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nft_regs {int dummy; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_expr {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eval ) (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nft_lookup_eval (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo*) ; 
 int /*<<< orphan*/  nft_meta_get_eval (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo*) ; 
 int /*<<< orphan*/  stub1 (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo*) ; 

__attribute__((used)) static void expr_call_ops_eval(const struct nft_expr *expr,
			       struct nft_regs *regs,
			       struct nft_pktinfo *pkt)
{
	unsigned long e = (unsigned long)expr->ops->eval;

	if (e == (unsigned long)nft_meta_get_eval)
		nft_meta_get_eval(expr, regs, pkt);
	else if (e == (unsigned long)nft_lookup_eval)
		nft_lookup_eval(expr, regs, pkt);
	else
		expr->ops->eval(expr, regs, pkt);
}