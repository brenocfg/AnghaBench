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
struct TYPE_2__ {int /*<<< orphan*/  active_duplex; int /*<<< orphan*/  active_speed; } ;
struct niu {TYPE_1__ link_config; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  MRVL88X2011_10G_PMD_STATUS_2 ; 
 int /*<<< orphan*/  MRVL88X2011_10G_XGXS_LANE_STAT ; 
 int /*<<< orphan*/  MRVL88X2011_LED_CTL_OFF ; 
 int /*<<< orphan*/  MRVL88X2011_LED_CTL_PCS_ACT ; 
 int MRVL88X2011_LNK_STATUS_OK ; 
 int /*<<< orphan*/  MRVL88X2011_PMA_PMD_STATUS_1 ; 
 int /*<<< orphan*/  MRVL88X2011_USER_DEV1_ADDR ; 
 int /*<<< orphan*/  MRVL88X2011_USER_DEV3_ADDR ; 
 int /*<<< orphan*/  MRVL88X2011_USER_DEV4_ADDR ; 
 int PHYXS_XGXS_LANE_STAT_ALINGED ; 
 int PHYXS_XGXS_LANE_STAT_LANE0 ; 
 int PHYXS_XGXS_LANE_STAT_LANE1 ; 
 int PHYXS_XGXS_LANE_STAT_LANE2 ; 
 int PHYXS_XGXS_LANE_STAT_LANE3 ; 
 int PHYXS_XGXS_LANE_STAT_MAGIC ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int mdio_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrvl88x2011_act_led (struct niu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int link_status_10g_mrvl(struct niu *np, int *link_up_p)
{
	int err, link_up, pma_status, pcs_status;

	link_up = 0;

	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			MRVL88X2011_10G_PMD_STATUS_2);
	if (err < 0)
		goto out;

	/* Check PMA/PMD Register: 1.0001.2 == 1 */
	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			MRVL88X2011_PMA_PMD_STATUS_1);
	if (err < 0)
		goto out;

	pma_status = ((err & MRVL88X2011_LNK_STATUS_OK) ? 1 : 0);

        /* Check PMC Register : 3.0001.2 == 1: read twice */
	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			MRVL88X2011_PMA_PMD_STATUS_1);
	if (err < 0)
		goto out;

	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			MRVL88X2011_PMA_PMD_STATUS_1);
	if (err < 0)
		goto out;

	pcs_status = ((err & MRVL88X2011_LNK_STATUS_OK) ? 1 : 0);

        /* Check XGXS Register : 4.0018.[0-3,12] */
	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV4_ADDR,
			MRVL88X2011_10G_XGXS_LANE_STAT);
	if (err < 0)
		goto out;

	if (err == (PHYXS_XGXS_LANE_STAT_ALINGED | PHYXS_XGXS_LANE_STAT_LANE3 |
		    PHYXS_XGXS_LANE_STAT_LANE2 | PHYXS_XGXS_LANE_STAT_LANE1 |
		    PHYXS_XGXS_LANE_STAT_LANE0 | PHYXS_XGXS_LANE_STAT_MAGIC |
		    0x800))
		link_up = (pma_status && pcs_status) ? 1 : 0;

	np->link_config.active_speed = SPEED_10000;
	np->link_config.active_duplex = DUPLEX_FULL;
	err = 0;
out:
	mrvl88x2011_act_led(np, (link_up ?
				 MRVL88X2011_LED_CTL_PCS_ACT :
				 MRVL88X2011_LED_CTL_OFF));

	*link_up_p = link_up;
	return err;
}