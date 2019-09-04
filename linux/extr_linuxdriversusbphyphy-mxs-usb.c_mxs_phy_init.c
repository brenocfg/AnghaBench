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
struct usb_phy {int dummy; } ;
struct mxs_phy {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_phy_clock_switch_delay () ; 
 int mxs_phy_hw_init (struct mxs_phy*) ; 
 struct mxs_phy* to_mxs_phy (struct usb_phy*) ; 

__attribute__((used)) static int mxs_phy_init(struct usb_phy *phy)
{
	int ret;
	struct mxs_phy *mxs_phy = to_mxs_phy(phy);

	mxs_phy_clock_switch_delay();
	ret = clk_prepare_enable(mxs_phy->clk);
	if (ret)
		return ret;

	return mxs_phy_hw_init(mxs_phy);
}