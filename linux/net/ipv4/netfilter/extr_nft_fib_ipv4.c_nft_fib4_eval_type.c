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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; int /*<<< orphan*/ * data; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_fib {size_t dreg; int flags; } ;
struct nft_expr {int dummy; } ;
struct net_device {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  _iph ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFTA_FIB_F_DADDR ; 
 int NFTA_FIB_F_IIF ; 
 int NFTA_FIB_F_OIF ; 
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  inet_dev_addr_type (int /*<<< orphan*/ ,struct net_device const*,int /*<<< orphan*/ ) ; 
 struct nft_fib* nft_expr_priv (struct nft_expr const*) ; 
 struct net_device* nft_in (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 struct net_device* nft_out (struct nft_pktinfo const*) ; 
 struct iphdr* skb_header_pointer (int /*<<< orphan*/ ,int,int,struct iphdr*) ; 
 int skb_network_offset (int /*<<< orphan*/ ) ; 

void nft_fib4_eval_type(const struct nft_expr *expr, struct nft_regs *regs,
			const struct nft_pktinfo *pkt)
{
	const struct nft_fib *priv = nft_expr_priv(expr);
	int noff = skb_network_offset(pkt->skb);
	u32 *dst = &regs->data[priv->dreg];
	const struct net_device *dev = NULL;
	struct iphdr *iph, _iph;
	__be32 addr;

	if (priv->flags & NFTA_FIB_F_IIF)
		dev = nft_in(pkt);
	else if (priv->flags & NFTA_FIB_F_OIF)
		dev = nft_out(pkt);

	iph = skb_header_pointer(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	if (priv->flags & NFTA_FIB_F_DADDR)
		addr = iph->daddr;
	else
		addr = iph->saddr;

	*dst = inet_dev_addr_type(nft_net(pkt), dev, addr);
}