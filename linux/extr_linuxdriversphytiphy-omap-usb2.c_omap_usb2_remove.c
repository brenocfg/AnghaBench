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
struct omap_usb {int /*<<< orphan*/  dev; int /*<<< orphan*/  phy; int /*<<< orphan*/  optclk; int /*<<< orphan*/  wkupclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct omap_usb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_usb2_remove(struct platform_device *pdev)
{
	struct omap_usb	*phy = platform_get_drvdata(pdev);

	clk_unprepare(phy->wkupclk);
	if (!IS_ERR(phy->optclk))
		clk_unprepare(phy->optclk);
	usb_remove_phy(&phy->phy);
	pm_runtime_disable(phy->dev);

	return 0;
}