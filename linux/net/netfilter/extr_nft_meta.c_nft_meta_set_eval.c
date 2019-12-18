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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct sk_buff {int nf_trace; void* secmark; int /*<<< orphan*/  pkt_type; void* priority; void* mark; } ;
struct nft_regs {void** data; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_meta {size_t sreg; int key; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
#define  NFT_META_MARK 132 
#define  NFT_META_NFTRACE 131 
#define  NFT_META_PKTTYPE 130 
#define  NFT_META_PRIORITY 129 
#define  NFT_META_SECMARK 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_reg_load8 (void**) ; 
 int /*<<< orphan*/  skb_pkt_type_ok (int /*<<< orphan*/ ) ; 

void nft_meta_set_eval(const struct nft_expr *expr,
		       struct nft_regs *regs,
		       const struct nft_pktinfo *pkt)
{
	const struct nft_meta *meta = nft_expr_priv(expr);
	struct sk_buff *skb = pkt->skb;
	u32 *sreg = &regs->data[meta->sreg];
	u32 value = *sreg;
	u8 value8;

	switch (meta->key) {
	case NFT_META_MARK:
		skb->mark = value;
		break;
	case NFT_META_PRIORITY:
		skb->priority = value;
		break;
	case NFT_META_PKTTYPE:
		value8 = nft_reg_load8(sreg);

		if (skb->pkt_type != value8 &&
		    skb_pkt_type_ok(value8) &&
		    skb_pkt_type_ok(skb->pkt_type))
			skb->pkt_type = value8;
		break;
	case NFT_META_NFTRACE:
		value8 = nft_reg_load8(sreg);

		skb->nf_trace = !!value8;
		break;
#ifdef CONFIG_NETWORK_SECMARK
	case NFT_META_SECMARK:
		skb->secmark = value;
		break;
#endif
	default:
		WARN_ON(1);
	}
}