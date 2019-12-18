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
struct nft_tunnel {size_t dreg; int key; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {void* code; } ;
struct nft_regs {TYPE_2__ verdict; int /*<<< orphan*/ * data; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_expr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int mode; TYPE_1__ key; } ;

/* Variables and functions */
 int IP_TUNNEL_INFO_TX ; 
 void* NFT_BREAK ; 
#define  NFT_TUNNEL_ID 129 
 int /*<<< orphan*/  NFT_TUNNEL_MODE_NONE ; 
 int /*<<< orphan*/  NFT_TUNNEL_MODE_RX ; 
 int /*<<< orphan*/  NFT_TUNNEL_MODE_TX ; 
#define  NFT_TUNNEL_PATH 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nft_tunnel* nft_expr_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  nft_reg_store8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct ip_tunnel_info* skb_tunnel_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_tunnel_get_eval(const struct nft_expr *expr,
				struct nft_regs *regs,
				const struct nft_pktinfo *pkt)
{
	const struct nft_tunnel *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	struct ip_tunnel_info *tun_info;

	tun_info = skb_tunnel_info(pkt->skb);

	switch (priv->key) {
	case NFT_TUNNEL_PATH:
		if (!tun_info) {
			nft_reg_store8(dest, false);
			return;
		}
		if (priv->mode == NFT_TUNNEL_MODE_NONE ||
		    (priv->mode == NFT_TUNNEL_MODE_RX &&
		     !(tun_info->mode & IP_TUNNEL_INFO_TX)) ||
		    (priv->mode == NFT_TUNNEL_MODE_TX &&
		     (tun_info->mode & IP_TUNNEL_INFO_TX)))
			nft_reg_store8(dest, true);
		else
			nft_reg_store8(dest, false);
		break;
	case NFT_TUNNEL_ID:
		if (!tun_info) {
			regs->verdict.code = NFT_BREAK;
			return;
		}
		if (priv->mode == NFT_TUNNEL_MODE_NONE ||
		    (priv->mode == NFT_TUNNEL_MODE_RX &&
		     !(tun_info->mode & IP_TUNNEL_INFO_TX)) ||
		    (priv->mode == NFT_TUNNEL_MODE_TX &&
		     (tun_info->mode & IP_TUNNEL_INFO_TX)))
			*dest = ntohl(tunnel_id_to_key32(tun_info->key.tun_id));
		else
			regs->verdict.code = NFT_BREAK;
		break;
	default:
		WARN_ON(1);
		regs->verdict.code = NFT_BREAK;
	}
}