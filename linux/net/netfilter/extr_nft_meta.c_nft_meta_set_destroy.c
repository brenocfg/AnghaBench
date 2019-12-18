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
struct nft_meta {scalar_t__ key; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFT_META_NFTRACE ; 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_trace_enabled ; 
 int /*<<< orphan*/  static_branch_dec (int /*<<< orphan*/ *) ; 

void nft_meta_set_destroy(const struct nft_ctx *ctx,
			  const struct nft_expr *expr)
{
	const struct nft_meta *priv = nft_expr_priv(expr);

	if (priv->key == NFT_META_NFTRACE)
		static_branch_dec(&nft_trace_enabled);
}