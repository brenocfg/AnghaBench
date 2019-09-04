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
struct phy_device {int dummy; } ;
struct mtk_mac {int /*<<< orphan*/  phy_flags; struct phy_device* phy_dev; struct mtk_eth* hw; } ;
struct mtk_eth {scalar_t__ mii_bus; TYPE_1__* phy; } ;
struct TYPE_2__ {struct phy_device** phy; scalar_t__* phy_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_PHY_FLAG_ATTACH ; 
 int /*<<< orphan*/  MTK_PHY_FLAG_PORT ; 
 struct phy_device* mdiobus_get_phy (scalar_t__,int) ; 
 int /*<<< orphan*/  phy_init (struct mtk_eth*,struct mtk_mac*,struct phy_device*) ; 

__attribute__((used)) static int mtk_phy_connect(struct mtk_mac *mac)
{
	struct mtk_eth *eth = mac->hw;
	int i;

	for (i = 0; i < 8; i++) {
		if (eth->phy->phy_node[i]) {
			if (!mac->phy_dev) {
				mac->phy_dev = eth->phy->phy[i];
				mac->phy_flags = MTK_PHY_FLAG_PORT;
			}
		} else if (eth->mii_bus) {
			struct phy_device *phy;

			phy = mdiobus_get_phy(eth->mii_bus, i);
			if (phy) {
				phy_init(eth, mac, phy);
				if (!mac->phy_dev) {
					mac->phy_dev = phy;
					mac->phy_flags = MTK_PHY_FLAG_ATTACH;
				}
			}
		}
	}

	return 0;
}