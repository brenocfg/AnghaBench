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
struct nft_rule {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  l3num; int /*<<< orphan*/  type; } ;
struct nft_offload_ctx {TYPE_2__ dep; struct net* net; } ;
struct nft_flow_rule {int /*<<< orphan*/  proto; } ;
struct nft_expr {TYPE_1__* ops; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int offload_flags; int (* offload ) (struct nft_offload_ctx*,struct nft_flow_rule*,struct nft_expr*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct nft_flow_rule* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFT_OFFLOAD_DEP_UNSPEC ; 
 int NFT_OFFLOAD_F_ACTION ; 
 int /*<<< orphan*/  kfree (struct nft_offload_ctx*) ; 
 struct nft_offload_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nft_expr* nft_expr_first (struct nft_rule const*) ; 
 struct nft_expr* nft_expr_last (struct nft_rule const*) ; 
 struct nft_expr* nft_expr_next (struct nft_expr*) ; 
 struct nft_flow_rule* nft_flow_rule_alloc (int) ; 
 int /*<<< orphan*/  nft_flow_rule_destroy (struct nft_flow_rule*) ; 
 int stub1 (struct nft_offload_ctx*,struct nft_flow_rule*,struct nft_expr*) ; 

struct nft_flow_rule *nft_flow_rule_create(struct net *net,
					   const struct nft_rule *rule)
{
	struct nft_offload_ctx *ctx;
	struct nft_flow_rule *flow;
	int num_actions = 0, err;
	struct nft_expr *expr;

	expr = nft_expr_first(rule);
	while (expr->ops && expr != nft_expr_last(rule)) {
		if (expr->ops->offload_flags & NFT_OFFLOAD_F_ACTION)
			num_actions++;

		expr = nft_expr_next(expr);
	}

	flow = nft_flow_rule_alloc(num_actions);
	if (!flow)
		return ERR_PTR(-ENOMEM);

	expr = nft_expr_first(rule);

	ctx = kzalloc(sizeof(struct nft_offload_ctx), GFP_KERNEL);
	if (!ctx) {
		err = -ENOMEM;
		goto err_out;
	}
	ctx->net = net;
	ctx->dep.type = NFT_OFFLOAD_DEP_UNSPEC;

	while (expr->ops && expr != nft_expr_last(rule)) {
		if (!expr->ops->offload) {
			err = -EOPNOTSUPP;
			goto err_out;
		}
		err = expr->ops->offload(ctx, flow, expr);
		if (err < 0)
			goto err_out;

		expr = nft_expr_next(expr);
	}
	flow->proto = ctx->dep.l3num;
	kfree(ctx);

	return flow;
err_out:
	kfree(ctx);
	nft_flow_rule_destroy(flow);

	return ERR_PTR(err);
}