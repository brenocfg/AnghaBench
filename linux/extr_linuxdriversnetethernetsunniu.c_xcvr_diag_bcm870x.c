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
typedef  int u16 ;
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM8704_PHYXS_DEV_ADDR ; 
 int /*<<< orphan*/  BCM8704_PMA_PMD_DEV_ADDR ; 
 int BCM8704_USER_ANALOG_STATUS0 ; 
 int /*<<< orphan*/  BCM8704_USER_DEV3_ADDR ; 
 int BCM8704_USER_TX_ALARM_STATUS ; 
 int MII_NWAYTEST ; 
 int MII_STAT1000 ; 
 int mdio_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int xcvr_diag_bcm870x(struct niu *np)
{
	u16 analog_stat0, tx_alarm_status;
	int err = 0;

#if 1
	err = mdio_read(np, np->phy_addr, BCM8704_PMA_PMD_DEV_ADDR,
			MII_STAT1000);
	if (err < 0)
		return err;
	pr_info("Port %u PMA_PMD(MII_STAT1000) [%04x]\n", np->port, err);

	err = mdio_read(np, np->phy_addr, BCM8704_USER_DEV3_ADDR, 0x20);
	if (err < 0)
		return err;
	pr_info("Port %u USER_DEV3(0x20) [%04x]\n", np->port, err);

	err = mdio_read(np, np->phy_addr, BCM8704_PHYXS_DEV_ADDR,
			MII_NWAYTEST);
	if (err < 0)
		return err;
	pr_info("Port %u PHYXS(MII_NWAYTEST) [%04x]\n", np->port, err);
#endif

	/* XXX dig this out it might not be so useful XXX */
	err = mdio_read(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_ANALOG_STATUS0);
	if (err < 0)
		return err;
	err = mdio_read(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_ANALOG_STATUS0);
	if (err < 0)
		return err;
	analog_stat0 = err;

	err = mdio_read(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_TX_ALARM_STATUS);
	if (err < 0)
		return err;
	err = mdio_read(np, np->phy_addr, BCM8704_USER_DEV3_ADDR,
			BCM8704_USER_TX_ALARM_STATUS);
	if (err < 0)
		return err;
	tx_alarm_status = err;

	if (analog_stat0 != 0x03fc) {
		if ((analog_stat0 == 0x43bc) && (tx_alarm_status != 0)) {
			pr_info("Port %u cable not connected or bad cable\n",
				np->port);
		} else if (analog_stat0 == 0x639c) {
			pr_info("Port %u optical module is bad or missing\n",
				np->port);
		}
	}

	return 0;
}