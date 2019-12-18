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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nft_regs {TYPE_1__ verdict; int /*<<< orphan*/ * data; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_meta {size_t dreg; int key; } ;
struct nft_expr {int dummy; } ;
struct net_device {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  NFT_BREAK ; 
#define  NFT_META_BRI_IIFNAME 131 
#define  NFT_META_BRI_IIFPVID 130 
#define  NFT_META_BRI_IIFVPROTO 129 
#define  NFT_META_BRI_OIFNAME 128 
 int /*<<< orphan*/  br_vlan_enabled (struct net_device const*) ; 
 int /*<<< orphan*/  br_vlan_get_proto (struct net_device const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_vlan_get_pvid_rcu (struct net_device const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct nft_meta* nft_expr_priv (struct nft_expr const*) ; 
 struct net_device* nft_in (struct nft_pktinfo const*) ; 
 struct net_device* nft_meta_get_bridge (struct net_device const*) ; 
 void nft_meta_get_eval (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo const*) ; 
 struct net_device* nft_out (struct nft_pktinfo const*) ; 
 int /*<<< orphan*/  nft_reg_store16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_meta_bridge_get_eval(const struct nft_expr *expr,
				     struct nft_regs *regs,
				     const struct nft_pktinfo *pkt)
{
	const struct nft_meta *priv = nft_expr_priv(expr);
	const struct net_device *in = nft_in(pkt), *out = nft_out(pkt);
	u32 *dest = &regs->data[priv->dreg];
	const struct net_device *br_dev;

	switch (priv->key) {
	case NFT_META_BRI_IIFNAME:
		br_dev = nft_meta_get_bridge(in);
		break;
	case NFT_META_BRI_OIFNAME:
		br_dev = nft_meta_get_bridge(out);
		break;
	case NFT_META_BRI_IIFPVID: {
		u16 p_pvid;

		br_dev = nft_meta_get_bridge(in);
		if (!br_dev || !br_vlan_enabled(br_dev))
			goto err;

		br_vlan_get_pvid_rcu(in, &p_pvid);
		nft_reg_store16(dest, p_pvid);
		return;
	}
	case NFT_META_BRI_IIFVPROTO: {
		u16 p_proto;

		br_dev = nft_meta_get_bridge(in);
		if (!br_dev || !br_vlan_enabled(br_dev))
			goto err;

		br_vlan_get_proto(br_dev, &p_proto);
		nft_reg_store16(dest, htons(p_proto));
		return;
	}
	default:
		return nft_meta_get_eval(expr, regs, pkt);
	}

	strncpy((char *)dest, br_dev ? br_dev->name : "", IFNAMSIZ);
	return;
err:
	regs->verdict.code = NFT_BREAK;
}