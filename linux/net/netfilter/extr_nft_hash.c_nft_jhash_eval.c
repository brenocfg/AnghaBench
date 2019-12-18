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
struct nft_regs {int /*<<< orphan*/ * data; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_jhash {size_t sreg; size_t dreg; int offset; int /*<<< orphan*/  modulus; int /*<<< orphan*/  seed; int /*<<< orphan*/  len; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_jhash* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_jhash_eval(const struct nft_expr *expr,
			   struct nft_regs *regs,
			   const struct nft_pktinfo *pkt)
{
	struct nft_jhash *priv = nft_expr_priv(expr);
	const void *data = &regs->data[priv->sreg];
	u32 h;

	h = reciprocal_scale(jhash(data, priv->len, priv->seed),
			     priv->modulus);

	regs->data[priv->dreg] = h + priv->offset;
}