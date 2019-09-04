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
struct nft_fib {size_t dreg; } ;
struct nft_expr {int dummy; } ;
struct ipv6hdr {int dummy; } ;
typedef  int /*<<< orphan*/  _iph ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_BREAK ; 
 int /*<<< orphan*/  __nft_fib6_eval_type (struct nft_fib const*,struct nft_pktinfo const*,struct ipv6hdr*) ; 
 struct nft_fib* nft_expr_priv (struct nft_expr const*) ; 
 struct ipv6hdr* skb_header_pointer (int /*<<< orphan*/ ,int,int,struct ipv6hdr*) ; 
 int skb_network_offset (int /*<<< orphan*/ ) ; 

void nft_fib6_eval_type(const struct nft_expr *expr, struct nft_regs *regs,
			const struct nft_pktinfo *pkt)
{
	const struct nft_fib *priv = nft_expr_priv(expr);
	int noff = skb_network_offset(pkt->skb);
	u32 *dest = &regs->data[priv->dreg];
	struct ipv6hdr *iph, _iph;

	iph = skb_header_pointer(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	*dest = __nft_fib6_eval_type(priv, pkt, iph);
}