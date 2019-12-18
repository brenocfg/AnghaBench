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
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct nft_queue {int flags; int /*<<< orphan*/  sreg_qnum; } ;
struct nft_expr {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NFTA_QUEUE_FLAGS ; 
 size_t NFTA_QUEUE_SREG_QNUM ; 
 int NFT_QUEUE_FLAG_CPU_FANOUT ; 
 int NFT_QUEUE_FLAG_MASK ; 
 struct nft_queue* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_parse_register (struct nlattr const* const) ; 
 int nft_validate_register_load (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const* const) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_queue_sreg_init(const struct nft_ctx *ctx,
			       const struct nft_expr *expr,
			       const struct nlattr * const tb[])
{
	struct nft_queue *priv = nft_expr_priv(expr);
	int err;

	priv->sreg_qnum = nft_parse_register(tb[NFTA_QUEUE_SREG_QNUM]);
	err = nft_validate_register_load(priv->sreg_qnum, sizeof(u32));
	if (err < 0)
		return err;

	if (tb[NFTA_QUEUE_FLAGS]) {
		priv->flags = ntohs(nla_get_be16(tb[NFTA_QUEUE_FLAGS]));
		if (priv->flags & ~NFT_QUEUE_FLAG_MASK)
			return -EINVAL;
		if (priv->flags & NFT_QUEUE_FLAG_CPU_FANOUT)
			return -EOPNOTSUPP;
	}

	return 0;
}