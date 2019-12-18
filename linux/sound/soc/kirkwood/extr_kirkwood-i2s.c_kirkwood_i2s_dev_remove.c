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
struct kirkwood_dma_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  extclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct kirkwood_dma_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kirkwood_i2s_dev_remove(struct platform_device *pdev)
{
	struct kirkwood_dma_data *priv = dev_get_drvdata(&pdev->dev);

	snd_soc_unregister_component(&pdev->dev);
	if (!IS_ERR(priv->extclk))
		clk_disable_unprepare(priv->extclk);
	clk_disable_unprepare(priv->clk);

	return 0;
}