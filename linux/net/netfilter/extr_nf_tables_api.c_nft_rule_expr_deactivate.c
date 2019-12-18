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
struct nft_rule {int dummy; } ;
struct nft_expr {TYPE_1__* ops; } ;
struct nft_ctx {int dummy; } ;
typedef  enum nft_trans_phase { ____Placeholder_nft_trans_phase } nft_trans_phase ;
struct TYPE_2__ {int /*<<< orphan*/  (* deactivate ) (struct nft_ctx const*,struct nft_expr*,int) ;} ;

/* Variables and functions */
 struct nft_expr* nft_expr_first (struct nft_rule*) ; 
 struct nft_expr* nft_expr_last (struct nft_rule*) ; 
 struct nft_expr* nft_expr_next (struct nft_expr*) ; 
 int /*<<< orphan*/  stub1 (struct nft_ctx const*,struct nft_expr*,int) ; 

__attribute__((used)) static void nft_rule_expr_deactivate(const struct nft_ctx *ctx,
				     struct nft_rule *rule,
				     enum nft_trans_phase phase)
{
	struct nft_expr *expr;

	expr = nft_expr_first(rule);
	while (expr != nft_expr_last(rule) && expr->ops) {
		if (expr->ops->deactivate)
			expr->ops->deactivate(ctx, expr, phase);

		expr = nft_expr_next(expr);
	}
}