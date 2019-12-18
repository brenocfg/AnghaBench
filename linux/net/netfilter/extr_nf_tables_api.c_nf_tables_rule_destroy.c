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
struct nft_rule {int dummy; } ;
struct nft_expr {scalar_t__ ops; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nft_rule*) ; 
 int /*<<< orphan*/  nf_tables_expr_destroy (struct nft_ctx const*,struct nft_expr*) ; 
 struct nft_expr* nft_expr_first (struct nft_rule*) ; 
 struct nft_expr* nft_expr_last (struct nft_rule*) ; 
 struct nft_expr* nft_expr_next (struct nft_expr*) ; 

__attribute__((used)) static void nf_tables_rule_destroy(const struct nft_ctx *ctx,
				   struct nft_rule *rule)
{
	struct nft_expr *expr, *next;

	/*
	 * Careful: some expressions might not be initialized in case this
	 * is called on error from nf_tables_newrule().
	 */
	expr = nft_expr_first(rule);
	while (expr != nft_expr_last(rule) && expr->ops) {
		next = nft_expr_next(expr);
		nf_tables_expr_destroy(ctx, expr);
		expr = next;
	}
	kfree(rule);
}