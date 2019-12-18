#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int data; scalar_t__ ip_summed; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_2__ verdict; int /*<<< orphan*/ * data; } ;
struct TYPE_3__ {int thoff; } ;
struct nft_pktinfo {TYPE_1__ xt; int /*<<< orphan*/  tprot_set; struct sk_buff* skb; } ;
struct nft_payload_set {size_t sreg; int base; int csum_offset; int offset; scalar_t__ csum_type; scalar_t__ len; scalar_t__ csum_flags; } ;
struct nft_expr {int dummy; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  NFT_BREAK ; 
 scalar_t__ NFT_PAYLOAD_CSUM_INET ; 
#define  NFT_PAYLOAD_LL_HEADER 130 
#define  NFT_PAYLOAD_NETWORK_HEADER 129 
#define  NFT_PAYLOAD_TRANSPORT_HEADER 128 
 int /*<<< orphan*/  csum_partial (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 struct nft_payload_set* nft_expr_priv (struct nft_expr const*) ; 
 scalar_t__ nft_payload_csum_inet (struct sk_buff*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nft_payload_l4csum_update (struct nft_pktinfo const*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ skb_store_bits (struct sk_buff*,int,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static void nft_payload_set_eval(const struct nft_expr *expr,
				 struct nft_regs *regs,
				 const struct nft_pktinfo *pkt)
{
	const struct nft_payload_set *priv = nft_expr_priv(expr);
	struct sk_buff *skb = pkt->skb;
	const u32 *src = &regs->data[priv->sreg];
	int offset, csum_offset;
	__wsum fsum, tsum;

	switch (priv->base) {
	case NFT_PAYLOAD_LL_HEADER:
		if (!skb_mac_header_was_set(skb))
			goto err;
		offset = skb_mac_header(skb) - skb->data;
		break;
	case NFT_PAYLOAD_NETWORK_HEADER:
		offset = skb_network_offset(skb);
		break;
	case NFT_PAYLOAD_TRANSPORT_HEADER:
		if (!pkt->tprot_set)
			goto err;
		offset = pkt->xt.thoff;
		break;
	default:
		BUG();
	}

	csum_offset = offset + priv->csum_offset;
	offset += priv->offset;

	if ((priv->csum_type == NFT_PAYLOAD_CSUM_INET || priv->csum_flags) &&
	    (priv->base != NFT_PAYLOAD_TRANSPORT_HEADER ||
	     skb->ip_summed != CHECKSUM_PARTIAL)) {
		fsum = skb_checksum(skb, offset, priv->len, 0);
		tsum = csum_partial(src, priv->len, 0);

		if (priv->csum_type == NFT_PAYLOAD_CSUM_INET &&
		    nft_payload_csum_inet(skb, src, fsum, tsum, csum_offset))
			goto err;

		if (priv->csum_flags &&
		    nft_payload_l4csum_update(pkt, skb, fsum, tsum) < 0)
			goto err;
	}

	if (skb_ensure_writable(skb, max(offset + priv->len, 0)) ||
	    skb_store_bits(skb, offset, src, priv->len) < 0)
		goto err;

	return;
err:
	regs->verdict.code = NFT_BREAK;
}