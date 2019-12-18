#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* code; } ;
struct nft_regs {TYPE_1__ verdict; int /*<<< orphan*/ * data; } ;
struct nft_range_expr {size_t sreg; int op; int /*<<< orphan*/  len; int /*<<< orphan*/  data_to; int /*<<< orphan*/  data_from; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 void* NFT_BREAK ; 
#define  NFT_RANGE_EQ 129 
#define  NFT_RANGE_NEQ 128 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nft_range_expr* nft_expr_priv (struct nft_expr const*) ; 

void nft_range_eval(const struct nft_expr *expr,
		    struct nft_regs *regs, const struct nft_pktinfo *pkt)
{
	const struct nft_range_expr *priv = nft_expr_priv(expr);
	int d1, d2;

	d1 = memcmp(&regs->data[priv->sreg], &priv->data_from, priv->len);
	d2 = memcmp(&regs->data[priv->sreg], &priv->data_to, priv->len);
	switch (priv->op) {
	case NFT_RANGE_EQ:
		if (d1 < 0 || d2 > 0)
			regs->verdict.code = NFT_BREAK;
		break;
	case NFT_RANGE_NEQ:
		if (d1 >= 0 && d2 <= 0)
			regs->verdict.code = NFT_BREAK;
		break;
	}
}