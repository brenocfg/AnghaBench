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
struct dim2_hdm {scalar_t__ io_base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct dim2_hdm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void rcar_h2_disable(struct platform_device *pdev)
{
	struct dim2_hdm *dev = platform_get_drvdata(pdev);

	clk_disable_unprepare(dev->clk);

	/* disable PLLs and LVDS drivers */
	writel(0x0, dev->io_base + 0x600);
}