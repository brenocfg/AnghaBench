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
struct nft_immediate_expr {int /*<<< orphan*/  dreg; int /*<<< orphan*/  data; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 void nft_data_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_dreg_to_type (int /*<<< orphan*/ ) ; 
 struct nft_immediate_expr* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static void nft_immediate_activate(const struct nft_ctx *ctx,
				   const struct nft_expr *expr)
{
	const struct nft_immediate_expr *priv = nft_expr_priv(expr);

	return nft_data_hold(&priv->data, nft_dreg_to_type(priv->dreg));
}