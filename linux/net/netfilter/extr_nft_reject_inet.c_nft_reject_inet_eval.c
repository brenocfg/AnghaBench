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
struct nft_reject {int /*<<< orphan*/  icmp_code; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
#define  NFPROTO_IPV4 132 
#define  NFPROTO_IPV6 131 
#define  NFT_REJECT_ICMPX_UNREACH 130 
#define  NFT_REJECT_ICMP_UNREACH 129 
#define  NFT_REJECT_TCP_RST 128 
 int /*<<< orphan*/  NF_DROP ; 
 int /*<<< orphan*/  nf_send_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_send_reset6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_send_unreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_send_unreach6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_reject* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_hook (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 int nft_pf (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_reject_icmp_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_reject_icmpv6_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_reject_inet_eval(const struct nft_expr *expr,
				 struct nft_regs *regs,
				 const struct nft_pktinfo *pkt)
{
	struct nft_reject *priv = nft_expr_priv(expr);

	switch (nft_pf(pkt)) {
	case NFPROTO_IPV4:
		switch (priv->type) {
		case NFT_REJECT_ICMP_UNREACH:
			nf_send_unreach(pkt->skb, priv->icmp_code,
					nft_hook(pkt));
			break;
		case NFT_REJECT_TCP_RST:
			nf_send_reset(nft_net(pkt), pkt->skb, nft_hook(pkt));
			break;
		case NFT_REJECT_ICMPX_UNREACH:
			nf_send_unreach(pkt->skb,
					nft_reject_icmp_code(priv->icmp_code),
					nft_hook(pkt));
			break;
		}
		break;
	case NFPROTO_IPV6:
		switch (priv->type) {
		case NFT_REJECT_ICMP_UNREACH:
			nf_send_unreach6(nft_net(pkt), pkt->skb,
					 priv->icmp_code, nft_hook(pkt));
			break;
		case NFT_REJECT_TCP_RST:
			nf_send_reset6(nft_net(pkt), pkt->skb, nft_hook(pkt));
			break;
		case NFT_REJECT_ICMPX_UNREACH:
			nf_send_unreach6(nft_net(pkt), pkt->skb,
					 nft_reject_icmpv6_code(priv->icmp_code),
					 nft_hook(pkt));
			break;
		}
		break;
	}

	regs->verdict.code = NF_DROP;
}