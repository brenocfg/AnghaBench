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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int features; } ;
struct mtk_mac {struct mtk_eth* hw; } ;
struct mtk_eth {int /*<<< orphan*/  vlan_map; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 size_t MTK_REG_MTK_DMA_VID_BASE ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__* mtk_reg_table ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mtk_vlan_rx_kill_vid(struct net_device *dev,
				__be16 proto, u16 vid)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;
	u32 idx = (vid & 0xf);

	if (!((mtk_reg_table[MTK_REG_MTK_DMA_VID_BASE]) &&
	      (dev->features & NETIF_F_HW_VLAN_CTAG_TX)))
		return 0;

	clear_bit(idx, &eth->vlan_map);

	return 0;
}