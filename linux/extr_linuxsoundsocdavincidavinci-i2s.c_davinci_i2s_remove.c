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
struct davinci_mcbsp_dev {int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 struct davinci_mcbsp_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_i2s_remove(struct platform_device *pdev)
{
	struct davinci_mcbsp_dev *dev = dev_get_drvdata(&pdev->dev);

	snd_soc_unregister_component(&pdev->dev);

	clk_disable(dev->clk);
	clk_put(dev->clk);
	dev->clk = NULL;

	return 0;
}