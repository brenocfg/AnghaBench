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
struct phy {int dummy; } ;
struct dm816x_usb_phy {int /*<<< orphan*/  usbphy_ctrl; int /*<<< orphan*/  syscon; int /*<<< orphan*/  dev; int /*<<< orphan*/  usb_ctrl; int /*<<< orphan*/  refclk; } ;

/* Variables and functions */
 unsigned int DM816X_USBPHY_CTRL_TXPREEMTUNE ; 
 unsigned int DM816X_USBPHY_CTRL_TXRISETUNE ; 
 unsigned int DM816X_USBPHY_CTRL_TXVREFTUNE ; 
 int DM816X_USB_CTRL_PHYCLKSRC ; 
 int DM816X_USB_CTRL_PHYSLEEP0 ; 
 int DM816X_USB_CTRL_PHYSLEEP1 ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct dm816x_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dm816x_usb_phy_init(struct phy *x)
{
	struct dm816x_usb_phy *phy = phy_get_drvdata(x);
	unsigned int val;
	int error;

	if (clk_get_rate(phy->refclk) != 24000000)
		dev_warn(phy->dev, "nonstandard phy refclk\n");

	/* Set PLL ref clock and put phys to sleep */
	error = regmap_update_bits(phy->syscon, phy->usb_ctrl,
				   DM816X_USB_CTRL_PHYCLKSRC |
				   DM816X_USB_CTRL_PHYSLEEP1 |
				   DM816X_USB_CTRL_PHYSLEEP0,
				   0);
	regmap_read(phy->syscon, phy->usb_ctrl, &val);
	if ((val & 3) != 0)
		dev_info(phy->dev,
			 "Working dm816x USB_CTRL! (0x%08x)\n",
			 val);

	/*
	 * TI kernel sets these values for "symmetrical eye diagram and
	 * better signal quality" so let's assume somebody checked the
	 * values with a scope and set them here too.
	 */
	regmap_read(phy->syscon, phy->usbphy_ctrl, &val);
	val |= DM816X_USBPHY_CTRL_TXRISETUNE |
		DM816X_USBPHY_CTRL_TXVREFTUNE |
		DM816X_USBPHY_CTRL_TXPREEMTUNE;
	regmap_write(phy->syscon, phy->usbphy_ctrl, val);

	return 0;
}