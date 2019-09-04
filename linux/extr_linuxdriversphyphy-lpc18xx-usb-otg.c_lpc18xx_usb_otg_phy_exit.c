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
struct lpc18xx_usb_otg_phy {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct lpc18xx_usb_otg_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int lpc18xx_usb_otg_phy_exit(struct phy *phy)
{
	struct lpc18xx_usb_otg_phy *lpc = phy_get_drvdata(phy);

	clk_unprepare(lpc->clk);

	return 0;
}