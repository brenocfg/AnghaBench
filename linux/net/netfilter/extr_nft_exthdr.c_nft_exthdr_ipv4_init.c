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
struct nft_exthdr {int type; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IPOPT_LSRR 131 
#define  IPOPT_RA 130 
#define  IPOPT_RR 129 
#define  IPOPT_SSRR 128 
 struct nft_exthdr* nft_expr_priv (struct nft_expr const*) ; 
 int nft_exthdr_init (struct nft_ctx const*,struct nft_expr const*,struct nlattr const* const*) ; 

__attribute__((used)) static int nft_exthdr_ipv4_init(const struct nft_ctx *ctx,
				const struct nft_expr *expr,
				const struct nlattr * const tb[])
{
	struct nft_exthdr *priv = nft_expr_priv(expr);
	int err = nft_exthdr_init(ctx, expr, tb);

	if (err < 0)
		return err;

	switch (priv->type) {
	case IPOPT_SSRR:
	case IPOPT_LSRR:
	case IPOPT_RR:
	case IPOPT_RA:
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}