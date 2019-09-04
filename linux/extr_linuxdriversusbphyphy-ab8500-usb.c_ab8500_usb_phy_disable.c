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
typedef  int /*<<< orphan*/  u8 ;
struct ab8500_usb {int /*<<< orphan*/  pinctrl; int /*<<< orphan*/  dev; int /*<<< orphan*/  pins_sleep; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_BIT_PHY_CTRL_DEVICE_EN ; 
 int /*<<< orphan*/  AB8500_BIT_PHY_CTRL_HOST_EN ; 
 int /*<<< orphan*/  AB8500_USB ; 
 int /*<<< orphan*/  AB8500_USB_PHY_CTRL_REG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PINCTRL_STATE_SLEEP ; 
 int /*<<< orphan*/  ab8500_usb_regulator_disable (struct ab8500_usb*) ; 
 int /*<<< orphan*/  ab8500_usb_wd_linkstatus (struct ab8500_usb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ab8500_usb_wd_workaround (struct ab8500_usb*) ; 
 int /*<<< orphan*/  abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pinctrl_lookup_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_put (int /*<<< orphan*/ ) ; 
 scalar_t__ pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_usb_phy_disable(struct ab8500_usb *ab, bool sel_host)
{
	u8 bit;
	bit = sel_host ? AB8500_BIT_PHY_CTRL_HOST_EN :
		AB8500_BIT_PHY_CTRL_DEVICE_EN;

	ab8500_usb_wd_linkstatus(ab, bit);

	abx500_mask_and_set_register_interruptible(ab->dev,
			AB8500_USB, AB8500_USB_PHY_CTRL_REG,
			bit, 0);

	/* Needed to disable the phy.*/
	ab8500_usb_wd_workaround(ab);

	clk_disable_unprepare(ab->sysclk);

	ab8500_usb_regulator_disable(ab);

	if (!IS_ERR(ab->pinctrl)) {
		/* configure USB pins to SLEEP state */
		ab->pins_sleep = pinctrl_lookup_state(ab->pinctrl,
				PINCTRL_STATE_SLEEP);

		if (IS_ERR(ab->pins_sleep))
			dev_dbg(ab->dev, "could not get sleep pinstate\n");
		else if (pinctrl_select_state(ab->pinctrl, ab->pins_sleep))
			dev_err(ab->dev, "could not set pins to sleep state\n");

		/*
		 * as USB pins are shared with iddet, release them to allow
		 * iddet to request them
		 */
		pinctrl_put(ab->pinctrl);
	}
}