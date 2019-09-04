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
struct nft_expr_ops {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nft_expr_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t NFTA_QUEUE_NUM ; 
 size_t NFTA_QUEUE_SREG_QNUM ; 
 int /*<<< orphan*/  init_hashrandom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jhash_initval ; 
 struct nft_expr_ops const nft_queue_ops ; 
 struct nft_expr_ops const nft_queue_sreg_ops ; 

__attribute__((used)) static const struct nft_expr_ops *
nft_queue_select_ops(const struct nft_ctx *ctx,
		     const struct nlattr * const tb[])
{
	if (tb[NFTA_QUEUE_NUM] && tb[NFTA_QUEUE_SREG_QNUM])
		return ERR_PTR(-EINVAL);

	init_hashrandom(&jhash_initval);

	if (tb[NFTA_QUEUE_NUM])
		return &nft_queue_ops;

	if (tb[NFTA_QUEUE_SREG_QNUM])
		return &nft_queue_sreg_ops;

	return ERR_PTR(-EINVAL);
}