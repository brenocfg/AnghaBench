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
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {int* data; TYPE_1__ verdict; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_fwd_netdev {size_t sreg_dev; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_STOLEN ; 
 int /*<<< orphan*/  nf_fwd_netdev_egress (struct nft_pktinfo const*,int) ; 
 struct nft_fwd_netdev* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static void nft_fwd_netdev_eval(const struct nft_expr *expr,
				struct nft_regs *regs,
				const struct nft_pktinfo *pkt)
{
	struct nft_fwd_netdev *priv = nft_expr_priv(expr);
	int oif = regs->data[priv->sreg_dev];

	nf_fwd_netdev_egress(pkt, oif);
	regs->verdict.code = NF_STOLEN;
}