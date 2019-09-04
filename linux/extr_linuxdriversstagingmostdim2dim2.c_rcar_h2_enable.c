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
struct dim2_hdm {scalar_t__ clk_speed; scalar_t__ io_base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ CLK_2048FS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dim2_hdm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int rcar_h2_enable(struct platform_device *pdev)
{
	struct dim2_hdm *dev = platform_get_drvdata(pdev);
	int ret;

	dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		return PTR_ERR(dev->clk);
	}

	ret = clk_prepare_enable(dev->clk);
	if (ret) {
		dev_err(&pdev->dev, "%s\n", "clk_prepare_enable failed");
		return ret;
	}

	if (dev->clk_speed >= CLK_2048FS) {
		/* enable MLP pll and LVDS drivers */
		writel(0x03, dev->io_base + 0x600);
		/* set bias */
		writel(0x888, dev->io_base + 0x38);
	} else {
		/* PLL */
		writel(0x04, dev->io_base + 0x600);
	}


	/* BBCR = 0b11 */
	writel(0x03, dev->io_base + 0x500);
	writel(0x0002FF02, dev->io_base + 0x508);

	return 0;
}