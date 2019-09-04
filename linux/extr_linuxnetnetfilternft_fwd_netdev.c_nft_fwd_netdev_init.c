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
struct nft_fwd_netdev {int /*<<< orphan*/  sreg_dev; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_FWD_SREG_DEV ; 
 struct nft_fwd_netdev* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nft_fwd_netdev_init(const struct nft_ctx *ctx,
			       const struct nft_expr *expr,
			       const struct nlattr * const tb[])
{
	struct nft_fwd_netdev *priv = nft_expr_priv(expr);

	if (tb[NFTA_FWD_SREG_DEV] == NULL)
		return -EINVAL;

	priv->sreg_dev = nft_parse_register(tb[NFTA_FWD_SREG_DEV]);
	return nft_validate_register_load(priv->sreg_dev, sizeof(int));
}