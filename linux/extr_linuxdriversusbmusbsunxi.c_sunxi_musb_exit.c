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
struct sunxi_glue {int /*<<< orphan*/  xceiv; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  phy; int /*<<< orphan*/  work; } ;
struct musb {TYPE_1__* controller; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNXI_MUSB_FL_HAS_RESET ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_HAS_SRAM ; 
 int /*<<< orphan*/  SUNXI_MUSB_FL_PHY_ON ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sunxi_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_usb_put_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_sram_release (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sunxi_musb_exit(struct musb *musb)
{
	struct sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	pm_runtime_put(musb->controller);

	cancel_work_sync(&glue->work);
	if (test_bit(SUNXI_MUSB_FL_PHY_ON, &glue->flags))
		phy_power_off(glue->phy);

	phy_exit(glue->phy);

	if (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags))
		reset_control_assert(glue->rst);

	clk_disable_unprepare(glue->clk);
	if (test_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags))
		sunxi_sram_release(musb->controller->parent);

	devm_usb_put_phy(glue->dev, glue->xceiv);

	return 0;
}