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
struct tcphdr {int /*<<< orphan*/  syn; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {void* code; } ;
struct nft_regs {TYPE_1__ verdict; int /*<<< orphan*/ * data; } ;
struct nft_pktinfo {struct sk_buff* skb; } ;
struct nft_osf {size_t dreg; } ;
struct nft_expr {int dummy; } ;

/* Variables and functions */
 void* NFT_BREAK ; 
 int /*<<< orphan*/  NFT_OSF_MAXGENRELEN ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 char* nf_osf_find (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_osf_fingers ; 
 struct nft_osf* nft_expr_priv (struct nft_expr const*) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcphdr*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_osf_eval(const struct nft_expr *expr, struct nft_regs *regs,
			 const struct nft_pktinfo *pkt)
{
	struct nft_osf *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	struct sk_buff *skb = pkt->skb;
	const struct tcphdr *tcp;
	struct tcphdr _tcph;
	const char *os_name;

	tcp = skb_header_pointer(skb, ip_hdrlen(skb),
				 sizeof(struct tcphdr), &_tcph);
	if (!tcp) {
		regs->verdict.code = NFT_BREAK;
		return;
	}
	if (!tcp->syn) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	os_name = nf_osf_find(skb, nf_osf_fingers);
	if (!os_name)
		strncpy((char *)dest, "unknown", NFT_OSF_MAXGENRELEN);
	else
		strncpy((char *)dest, os_name, NFT_OSF_MAXGENRELEN);
}