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
struct usb_phy {scalar_t__ io_priv; } ;
struct mxs_phy {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int BM_USBPHY_CTRL_CLKGATE ; 
 scalar_t__ HW_USBPHY_CTRL_CLR ; 
 scalar_t__ HW_USBPHY_CTRL_SET ; 
 scalar_t__ HW_USBPHY_PWD ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_phy_clock_switch_delay () ; 
 int mxs_phy_get_vbus_status (struct mxs_phy*) ; 
 int mxs_phy_is_low_speed_connection (struct mxs_phy*) ; 
 struct mxs_phy* to_mxs_phy (struct usb_phy*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_phy_suspend(struct usb_phy *x, int suspend)
{
	int ret;
	struct mxs_phy *mxs_phy = to_mxs_phy(x);
	bool low_speed_connection, vbus_is_on;

	low_speed_connection = mxs_phy_is_low_speed_connection(mxs_phy);
	vbus_is_on = mxs_phy_get_vbus_status(mxs_phy);

	if (suspend) {
		/*
		 * FIXME: Do not power down RXPWD1PT1 bit for low speed
		 * connect. The low speed connection will have problem at
		 * very rare cases during usb suspend and resume process.
		 */
		if (low_speed_connection & vbus_is_on) {
			/*
			 * If value to be set as pwd value is not 0xffffffff,
			 * several 32Khz cycles are needed.
			 */
			mxs_phy_clock_switch_delay();
			writel(0xffbfffff, x->io_priv + HW_USBPHY_PWD);
		} else {
			writel(0xffffffff, x->io_priv + HW_USBPHY_PWD);
		}
		writel(BM_USBPHY_CTRL_CLKGATE,
		       x->io_priv + HW_USBPHY_CTRL_SET);
		clk_disable_unprepare(mxs_phy->clk);
	} else {
		mxs_phy_clock_switch_delay();
		ret = clk_prepare_enable(mxs_phy->clk);
		if (ret)
			return ret;
		writel(BM_USBPHY_CTRL_CLKGATE,
		       x->io_priv + HW_USBPHY_CTRL_CLR);
		writel(0, x->io_priv + HW_USBPHY_PWD);
	}

	return 0;
}