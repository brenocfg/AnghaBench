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
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nft_ct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nft_ct_set_destroy (struct nft_ctx const*,struct nft_ct*) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_ct* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static void nft_ct_set_destroy(const struct nft_ctx *ctx,
			       const struct nft_expr *expr)
{
	struct nft_ct *priv = nft_expr_priv(expr);

	__nft_ct_set_destroy(ctx, priv);
	nf_ct_netns_put(ctx->net, ctx->family);
}