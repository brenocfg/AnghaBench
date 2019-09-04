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
struct platform_device {int dummy; } ;
struct cpcap_phy_ddata {int /*<<< orphan*/  vusb; int /*<<< orphan*/  refclk; int /*<<< orphan*/  detect_work; int /*<<< orphan*/  phy; int /*<<< orphan*/  dev; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_VBUS_OFF ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int cpcap_usb_set_uart_mode (struct cpcap_phy_ddata*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int musb_mailbox (int /*<<< orphan*/ ) ; 
 struct cpcap_phy_ddata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpcap_usb_phy_remove(struct platform_device *pdev)
{
	struct cpcap_phy_ddata *ddata = platform_get_drvdata(pdev);
	int error;

	atomic_set(&ddata->active, 0);
	error = cpcap_usb_set_uart_mode(ddata);
	if (error)
		dev_err(ddata->dev, "could not set UART mode\n");

	error = musb_mailbox(MUSB_VBUS_OFF);
	if (error)
		dev_err(ddata->dev, "could not set mailbox\n");

	usb_remove_phy(&ddata->phy);
	cancel_delayed_work_sync(&ddata->detect_work);
	clk_unprepare(ddata->refclk);
	regulator_disable(ddata->vusb);

	return 0;
}