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
typedef  int u8 ;
struct net_device {int const* dev_addr; int flags; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; struct net_device* ndev; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;
typedef  int /*<<< orphan*/  discvr_pattern ;

/* Variables and functions */
 int ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  WOW_LIST_ID ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int ath6kl_wmi_add_wow_pattern_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int const*,int const*) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int*) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 

__attribute__((used)) static int ath6kl_wow_sta(struct ath6kl *ar, struct ath6kl_vif *vif)
{
	struct net_device *ndev = vif->ndev;
	static const u8 discvr_pattern[] = { 0xe0, 0x00, 0x00, 0xf8 };
	static const u8 discvr_mask[] = { 0xf0, 0x00, 0x00, 0xf8 };
	u8 discvr_offset = 38;
	u8 mac_mask[ETH_ALEN];
	int ret;

	/* Setup unicast pkt pattern */
	eth_broadcast_addr(mac_mask);
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
				vif->fw_vif_idx, WOW_LIST_ID,
				ETH_ALEN, 0, ndev->dev_addr,
				mac_mask);
	if (ret) {
		ath6kl_err("failed to add WOW unicast pattern\n");
		return ret;
	}

	/*
	 * Setup multicast pattern for mDNS 224.0.0.251,
	 * SSDP 239.255.255.250 and LLMNR 224.0.0.252
	 */
	if ((ndev->flags & IFF_ALLMULTI) ||
	    (ndev->flags & IFF_MULTICAST && netdev_mc_count(ndev) > 0)) {
		ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
				vif->fw_vif_idx, WOW_LIST_ID,
				sizeof(discvr_pattern), discvr_offset,
				discvr_pattern, discvr_mask);
		if (ret) {
			ath6kl_err("failed to add WOW mDNS/SSDP/LLMNR pattern\n");
			return ret;
		}
	}

	return 0;
}