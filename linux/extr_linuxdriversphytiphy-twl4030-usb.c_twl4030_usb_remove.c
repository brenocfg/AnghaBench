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
struct twl4030_usb {int /*<<< orphan*/  dev; int /*<<< orphan*/  linkstat; int /*<<< orphan*/  id_workaround_work; int /*<<< orphan*/  phy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CLK_CTRL ; 
 int PHY_CLK_CTRL_CLK32K_EN ; 
 int PHY_CLK_CTRL_CLOCKGATING_EN ; 
 int /*<<< orphan*/  POWER_CTRL ; 
 int /*<<< orphan*/  POWER_CTRL_OTG_ENAB ; 
 int REQ_PHY_DPLL_CLK ; 
 scalar_t__ cable_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_vbus ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct twl4030_usb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_usb_clear_bits (struct twl4030_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl4030_usb_read (struct twl4030_usb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_usb_set_mode (struct twl4030_usb*,int) ; 
 int /*<<< orphan*/  twl4030_usb_write (struct twl4030_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int twl4030_usb_remove(struct platform_device *pdev)
{
	struct twl4030_usb *twl = platform_get_drvdata(pdev);
	int val;

	usb_remove_phy(&twl->phy);
	pm_runtime_get_sync(twl->dev);
	cancel_delayed_work(&twl->id_workaround_work);
	device_remove_file(twl->dev, &dev_attr_vbus);

	/* set transceiver mode to power on defaults */
	twl4030_usb_set_mode(twl, -1);

	/* idle ulpi before powering off */
	if (cable_present(twl->linkstat))
		pm_runtime_put_noidle(twl->dev);
	pm_runtime_mark_last_busy(twl->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	pm_runtime_put_sync(twl->dev);
	pm_runtime_disable(twl->dev);

	/* autogate 60MHz ULPI clock,
	 * clear dpll clock request for i2c access,
	 * disable 32KHz
	 */
	val = twl4030_usb_read(twl, PHY_CLK_CTRL);
	if (val >= 0) {
		val |= PHY_CLK_CTRL_CLOCKGATING_EN;
		val &= ~(PHY_CLK_CTRL_CLK32K_EN | REQ_PHY_DPLL_CLK);
		twl4030_usb_write(twl, PHY_CLK_CTRL, (u8)val);
	}

	/* disable complete OTG block */
	twl4030_usb_clear_bits(twl, POWER_CTRL, POWER_CTRL_OTG_ENAB);

	return 0;
}