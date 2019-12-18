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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ep93xx_i2s_info {int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; int /*<<< orphan*/  lrclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct ep93xx_i2s_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ep93xx_i2s_remove(struct platform_device *pdev)
{
	struct ep93xx_i2s_info *info = dev_get_drvdata(&pdev->dev);

	clk_put(info->lrclk);
	clk_put(info->sclk);
	clk_put(info->mclk);
	return 0;
}