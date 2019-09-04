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
struct TYPE_3__ {scalar_t__ level; } ;
struct TYPE_4__ {TYPE_1__ log; } ;
struct nf_loginfo {int /*<<< orphan*/  type; TYPE_2__ u; } ;
struct nft_log {scalar_t__ prefix; struct nf_loginfo loginfo; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 scalar_t__ NFT_LOGLEVEL_AUDIT ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  nf_logger_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_log* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_log_null_prefix ; 

__attribute__((used)) static void nft_log_destroy(const struct nft_ctx *ctx,
			    const struct nft_expr *expr)
{
	struct nft_log *priv = nft_expr_priv(expr);
	struct nf_loginfo *li = &priv->loginfo;

	if (priv->prefix != nft_log_null_prefix)
		kfree(priv->prefix);

	if (li->u.log.level == NFT_LOGLEVEL_AUDIT)
		return;

	nf_logger_put(ctx->family, li->type);
}