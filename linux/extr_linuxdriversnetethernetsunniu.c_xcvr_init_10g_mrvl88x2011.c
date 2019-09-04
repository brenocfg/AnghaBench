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
struct TYPE_2__ {scalar_t__ loopback_mode; } ;
struct niu {int /*<<< orphan*/  phy_addr; TYPE_1__ link_config; } ;

/* Variables and functions */
 scalar_t__ LOOPBACK_MAC ; 
 int /*<<< orphan*/  MRVL88X2011_10G_PMD_TX_DIS ; 
 int MRVL88X2011_ENA_PMDTX ; 
 int MRVL88X2011_ENA_XFPREFCLK ; 
 int /*<<< orphan*/  MRVL88X2011_GENERAL_CTL ; 
 int /*<<< orphan*/  MRVL88X2011_LED_BLKRATE_134MS ; 
 int /*<<< orphan*/  MRVL88X2011_LED_CTL_OFF ; 
 int MRVL88X2011_LOOPBACK ; 
 int /*<<< orphan*/  MRVL88X2011_PMA_PMD_CTL_1 ; 
 int /*<<< orphan*/  MRVL88X2011_USER_DEV1_ADDR ; 
 int /*<<< orphan*/  MRVL88X2011_USER_DEV3_ADDR ; 
 int mdio_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mdio_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mrvl88x2011_act_led (struct niu*,int /*<<< orphan*/ ) ; 
 int mrvl88x2011_led_blink_rate (struct niu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xcvr_init_10g_mrvl88x2011(struct niu *np)
{
	int	err;

	/* Set LED functions */
	err = mrvl88x2011_led_blink_rate(np, MRVL88X2011_LED_BLKRATE_134MS);
	if (err)
		return err;

	/* led activity */
	err = mrvl88x2011_act_led(np, MRVL88X2011_LED_CTL_OFF);
	if (err)
		return err;

	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			MRVL88X2011_GENERAL_CTL);
	if (err < 0)
		return err;

	err |= MRVL88X2011_ENA_XFPREFCLK;

	err = mdio_write(np, np->phy_addr, MRVL88X2011_USER_DEV3_ADDR,
			 MRVL88X2011_GENERAL_CTL, err);
	if (err < 0)
		return err;

	err = mdio_read(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			MRVL88X2011_PMA_PMD_CTL_1);
	if (err < 0)
		return err;

	if (np->link_config.loopback_mode == LOOPBACK_MAC)
		err |= MRVL88X2011_LOOPBACK;
	else
		err &= ~MRVL88X2011_LOOPBACK;

	err = mdio_write(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			 MRVL88X2011_PMA_PMD_CTL_1, err);
	if (err < 0)
		return err;

	/* Enable PMD  */
	return mdio_write(np, np->phy_addr, MRVL88X2011_USER_DEV1_ADDR,
			  MRVL88X2011_10G_PMD_TX_DIS, MRVL88X2011_ENA_PMDTX);
}