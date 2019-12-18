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
struct xt_tgdtor_param {struct xt_target* target; int /*<<< orphan*/  family; void* targinfo; int /*<<< orphan*/  net; } ;
struct xt_target {int /*<<< orphan*/  (* destroy ) (struct xt_tgdtor_param*) ;struct module* me; } ;
struct nft_expr {TYPE_1__* ops; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct module {int dummy; } ;
struct TYPE_2__ {struct xt_target* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 void* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  stub1 (struct xt_tgdtor_param*) ; 

__attribute__((used)) static void
nft_target_destroy(const struct nft_ctx *ctx, const struct nft_expr *expr)
{
	struct xt_target *target = expr->ops->data;
	void *info = nft_expr_priv(expr);
	struct module *me = target->me;
	struct xt_tgdtor_param par;

	par.net = ctx->net;
	par.target = target;
	par.targinfo = info;
	par.family = ctx->family;
	if (par.target->destroy != NULL)
		par.target->destroy(&par);

	module_put(me);
	kfree(expr->ops);
}