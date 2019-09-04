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
struct nft_fwd_neigh {int nfproto; void* sreg_addr; void* sreg_dev; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 size_t NFTA_FWD_NFPROTO ; 
 size_t NFTA_FWD_SREG_ADDR ; 
 size_t NFTA_FWD_SREG_DEV ; 
 struct nft_fwd_neigh* nft_expr_priv (struct nft_expr const*) ; 
 void* nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_load (void*,unsigned int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_fwd_neigh_init(const struct nft_ctx *ctx,
			      const struct nft_expr *expr,
			      const struct nlattr * const tb[])
{
	struct nft_fwd_neigh *priv = nft_expr_priv(expr);
	unsigned int addr_len;
	int err;

	if (!tb[NFTA_FWD_SREG_DEV] ||
	    !tb[NFTA_FWD_SREG_ADDR] ||
	    !tb[NFTA_FWD_NFPROTO])
		return -EINVAL;

	priv->sreg_dev = nft_parse_register(tb[NFTA_FWD_SREG_DEV]);
	priv->sreg_addr = nft_parse_register(tb[NFTA_FWD_SREG_ADDR]);
	priv->nfproto = ntohl(nla_get_be32(tb[NFTA_FWD_NFPROTO]));

	switch (priv->nfproto) {
	case NFPROTO_IPV4:
		addr_len = sizeof(struct in_addr);
		break;
	case NFPROTO_IPV6:
		addr_len = sizeof(struct in6_addr);
		break;
	default:
		return -EOPNOTSUPP;
	}

	err = nft_validate_register_load(priv->sreg_dev, sizeof(int));
	if (err < 0)
		return err;

	return nft_validate_register_load(priv->sreg_addr, addr_len);
}