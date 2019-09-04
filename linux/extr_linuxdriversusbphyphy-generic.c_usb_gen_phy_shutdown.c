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
struct usb_phy_generic {int /*<<< orphan*/  vcc; int /*<<< orphan*/  clk; int /*<<< orphan*/  gpiod_reset; } ;
struct usb_phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct usb_phy_generic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 scalar_t__ regulator_disable (int /*<<< orphan*/ ) ; 

void usb_gen_phy_shutdown(struct usb_phy *phy)
{
	struct usb_phy_generic *nop = dev_get_drvdata(phy->dev);

	gpiod_set_value_cansleep(nop->gpiod_reset, 1);

	if (!IS_ERR(nop->clk))
		clk_disable_unprepare(nop->clk);

	if (!IS_ERR(nop->vcc)) {
		if (regulator_disable(nop->vcc))
			dev_err(phy->dev, "Failed to disable power\n");
	}
}