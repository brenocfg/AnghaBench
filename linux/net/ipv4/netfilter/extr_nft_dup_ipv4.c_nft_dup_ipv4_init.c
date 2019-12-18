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
struct nft_dup_ipv4 {void* sreg_dev; void* sreg_addr; } ;
struct nft_ctx {int dummy; } ;
struct in_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFTA_DUP_SREG_ADDR ; 
 size_t NFTA_DUP_SREG_DEV ; 
 struct nft_dup_ipv4* nft_expr_priv (struct nft_expr const*) ; 
 void* nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_load (void*,int) ; 

__attribute__((used)) static int nft_dup_ipv4_init(const struct nft_ctx *ctx,
			     const struct nft_expr *expr,
			     const struct nlattr * const tb[])
{
	struct nft_dup_ipv4 *priv = nft_expr_priv(expr);
	int err;

	if (tb[NFTA_DUP_SREG_ADDR] == NULL)
		return -EINVAL;

	priv->sreg_addr = nft_parse_register(tb[NFTA_DUP_SREG_ADDR]);
	err = nft_validate_register_load(priv->sreg_addr, sizeof(struct in_addr));
	if (err < 0)
		return err;

	if (tb[NFTA_DUP_SREG_DEV] != NULL) {
		priv->sreg_dev = nft_parse_register(tb[NFTA_DUP_SREG_DEV]);
		return nft_validate_register_load(priv->sreg_dev, sizeof(int));
	}
	return 0;
}