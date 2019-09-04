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
struct mii_phy {unsigned short (* mdio_read ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int mii_id; TYPE_1__* def; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  dev; } ;
struct spider_net_card {int /*<<< orphan*/  netdev; struct mii_phy phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  SPIDER_NET_DMASEL_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_GDTDMASEL ; 
 int /*<<< orphan*/  SPIDER_NET_GPCCTRL ; 
 int /*<<< orphan*/  SPIDER_NET_PHY_CTRL_VALUE ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 unsigned short spider_net_read_phy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spider_net_write_phy ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sungem_phy_probe (struct mii_phy*,int) ; 

__attribute__((used)) static int
spider_net_setup_phy(struct spider_net_card *card)
{
	struct mii_phy *phy = &card->phy;

	spider_net_write_reg(card, SPIDER_NET_GDTDMASEL,
			     SPIDER_NET_DMASEL_VALUE);
	spider_net_write_reg(card, SPIDER_NET_GPCCTRL,
			     SPIDER_NET_PHY_CTRL_VALUE);

	phy->dev = card->netdev;
	phy->mdio_read = spider_net_read_phy;
	phy->mdio_write = spider_net_write_phy;

	for (phy->mii_id = 1; phy->mii_id <= 31; phy->mii_id++) {
		unsigned short id;
		id = spider_net_read_phy(card->netdev, phy->mii_id, MII_BMSR);
		if (id != 0x0000 && id != 0xffff) {
			if (!sungem_phy_probe(phy, phy->mii_id)) {
				pr_info("Found %s.\n", phy->def->name);
				break;
			}
		}
	}

	return 0;
}