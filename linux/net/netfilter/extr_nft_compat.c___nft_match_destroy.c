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
struct xt_mtdtor_param {struct xt_match* match; int /*<<< orphan*/  family; void* matchinfo; int /*<<< orphan*/  net; } ;
struct xt_match {int /*<<< orphan*/  (* destroy ) (struct xt_mtdtor_param*) ;struct module* me; } ;
struct nft_expr {TYPE_1__* ops; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct module {int dummy; } ;
struct TYPE_2__ {struct xt_match* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  stub1 (struct xt_mtdtor_param*) ; 

__attribute__((used)) static void
__nft_match_destroy(const struct nft_ctx *ctx, const struct nft_expr *expr,
		    void *info)
{
	struct xt_match *match = expr->ops->data;
	struct module *me = match->me;
	struct xt_mtdtor_param par;

	par.net = ctx->net;
	par.match = match;
	par.matchinfo = info;
	par.family = ctx->family;
	if (par.match->destroy != NULL)
		par.match->destroy(&par);

	module_put(me);
	kfree(expr->ops);
}