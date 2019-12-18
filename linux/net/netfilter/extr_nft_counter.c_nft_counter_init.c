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
struct nlattr {int dummy; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;
struct nft_counter_percpu_priv {int dummy; } ;

/* Variables and functions */
 int nft_counter_do_init (struct nlattr const* const*,struct nft_counter_percpu_priv*) ; 
 struct nft_counter_percpu_priv* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static int nft_counter_init(const struct nft_ctx *ctx,
			    const struct nft_expr *expr,
			    const struct nlattr * const tb[])
{
	struct nft_counter_percpu_priv *priv = nft_expr_priv(expr);

	return nft_counter_do_init(tb, priv);
}