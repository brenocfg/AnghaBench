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
typedef  int u32 ;
struct wl1271 {int fuse_oui_addr; int fuse_nic_addr; int /*<<< orphan*/ * ptable; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 size_t PART_DOWN ; 
 size_t PART_TOP_PRCM_ELP_SOC ; 
 int /*<<< orphan*/  WL18XX_REG_FUSE_BD_ADDR_1 ; 
 int /*<<< orphan*/  WL18XX_REG_FUSE_BD_ADDR_2 ; 
 int /*<<< orphan*/  eth_random_addr (int*) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 
 int wlcore_read32 (struct wl1271*,int /*<<< orphan*/ ,int*) ; 
 int wlcore_set_partition (struct wl1271*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wl18xx_get_mac(struct wl1271 *wl)
{
	u32 mac1, mac2;
	int ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
	if (ret < 0)
		goto out;

	ret = wlcore_read32(wl, WL18XX_REG_FUSE_BD_ADDR_1, &mac1);
	if (ret < 0)
		goto out;

	ret = wlcore_read32(wl, WL18XX_REG_FUSE_BD_ADDR_2, &mac2);
	if (ret < 0)
		goto out;

	/* these are the two parts of the BD_ADDR */
	wl->fuse_oui_addr = ((mac2 & 0xffff) << 8) +
		((mac1 & 0xff000000) >> 24);
	wl->fuse_nic_addr = (mac1 & 0xffffff);

	if (!wl->fuse_oui_addr && !wl->fuse_nic_addr) {
		u8 mac[ETH_ALEN];

		eth_random_addr(mac);

		wl->fuse_oui_addr = (mac[0] << 16) + (mac[1] << 8) + mac[2];
		wl->fuse_nic_addr = (mac[3] << 16) + (mac[4] << 8) + mac[5];
		wl1271_warning("MAC address from fuse not available, using random locally administered addresses.");
	}

	ret = wlcore_set_partition(wl, &wl->ptable[PART_DOWN]);

out:
	return ret;
}