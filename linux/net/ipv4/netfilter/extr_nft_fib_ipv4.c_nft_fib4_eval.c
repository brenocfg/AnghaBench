#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; scalar_t__* data; } ;
struct nft_pktinfo {TYPE_2__* skb; } ;
struct nft_fib {size_t dreg; int flags; } ;
struct nft_expr {int dummy; } ;
struct net_device {int dummy; } ;
struct iphdr {int tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct flowi4 {int flowi4_tos; void* saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  flowi4_iif; int /*<<< orphan*/  flowi4_scope; } ;
struct fib_result {int type; int /*<<< orphan*/  fi; } ;
typedef  int /*<<< orphan*/  _iph ;
struct TYPE_6__ {int /*<<< orphan*/  mark; struct net_device const* dev; } ;

/* Variables and functions */
 int DSCP_BITS ; 
 int /*<<< orphan*/  FIB_LOOKUP_IGNORE_LINKSTATE ; 
 struct net_device* FIB_RES_DEV (struct fib_result) ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int NFTA_FIB_F_DADDR ; 
 int NFTA_FIB_F_IIF ; 
 int NFTA_FIB_F_MARK ; 
 int NFTA_FIB_F_OIF ; 
 int /*<<< orphan*/  NFT_BREAK ; 
 scalar_t__ NF_INET_PRE_ROUTING ; 
#define  RTN_LOCAL 129 
#define  RTN_UNICAST 128 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  fib_info_nh_uses_dev (int /*<<< orphan*/ ,struct net_device const*) ; 
 scalar_t__ fib_lookup (int /*<<< orphan*/ ,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 void* get_saddr (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_lbcast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_zeronet (int /*<<< orphan*/ ) ; 
 struct nft_fib* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_fib_is_loopback (TYPE_2__*,struct net_device const*) ; 
 int /*<<< orphan*/  nft_fib_store_result (scalar_t__*,struct nft_fib const*,struct net_device const*) ; 
 scalar_t__ nft_hook (struct nft_pktinfo const*) ; 
 struct net_device const* nft_in (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 struct net_device* nft_out (struct nft_pktinfo const*) ; 
 struct iphdr* skb_header_pointer (TYPE_2__*,int,int,struct iphdr*) ; 
 int skb_network_offset (TYPE_2__*) ; 

void nft_fib4_eval(const struct nft_expr *expr, struct nft_regs *regs,
		   const struct nft_pktinfo *pkt)
{
	const struct nft_fib *priv = nft_expr_priv(expr);
	int noff = skb_network_offset(pkt->skb);
	u32 *dest = &regs->data[priv->dreg];
	struct iphdr *iph, _iph;
	struct fib_result res;
	struct flowi4 fl4 = {
		.flowi4_scope = RT_SCOPE_UNIVERSE,
		.flowi4_iif = LOOPBACK_IFINDEX,
	};
	const struct net_device *oif;
	const struct net_device *found;

	/*
	 * Do not set flowi4_oif, it restricts results (for example, asking
	 * for oif 3 will get RTN_UNICAST result even if the daddr exits
	 * on another interface.
	 *
	 * Search results for the desired outinterface instead.
	 */
	if (priv->flags & NFTA_FIB_F_OIF)
		oif = nft_out(pkt);
	else if (priv->flags & NFTA_FIB_F_IIF)
		oif = nft_in(pkt);
	else
		oif = NULL;

	if (nft_hook(pkt) == NF_INET_PRE_ROUTING &&
	    nft_fib_is_loopback(pkt->skb, nft_in(pkt))) {
		nft_fib_store_result(dest, priv, nft_in(pkt));
		return;
	}

	iph = skb_header_pointer(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	if (ipv4_is_zeronet(iph->saddr)) {
		if (ipv4_is_lbcast(iph->daddr) ||
		    ipv4_is_local_multicast(iph->daddr)) {
			nft_fib_store_result(dest, priv, pkt->skb->dev);
			return;
		}
	}

	if (priv->flags & NFTA_FIB_F_MARK)
		fl4.flowi4_mark = pkt->skb->mark;

	fl4.flowi4_tos = iph->tos & DSCP_BITS;

	if (priv->flags & NFTA_FIB_F_DADDR) {
		fl4.daddr = iph->daddr;
		fl4.saddr = get_saddr(iph->saddr);
	} else {
		fl4.daddr = iph->saddr;
		fl4.saddr = get_saddr(iph->daddr);
	}

	*dest = 0;

	if (fib_lookup(nft_net(pkt), &fl4, &res, FIB_LOOKUP_IGNORE_LINKSTATE))
		return;

	switch (res.type) {
	case RTN_UNICAST:
		break;
	case RTN_LOCAL: /* Should not see RTN_LOCAL here */
		return;
	default:
		break;
	}

       if (!oif) {
               found = FIB_RES_DEV(res);
	} else {
		if (!fib_info_nh_uses_dev(res.fi, oif))
			return;

		found = oif;
	}

	nft_fib_store_result(dest, priv, found);
}