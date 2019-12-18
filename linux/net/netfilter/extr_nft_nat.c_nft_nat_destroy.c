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
struct nft_nat {int /*<<< orphan*/  family; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_nat* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static void
nft_nat_destroy(const struct nft_ctx *ctx, const struct nft_expr *expr)
{
	const struct nft_nat *priv = nft_expr_priv(expr);

	nf_ct_netns_put(ctx->net, priv->family);
}