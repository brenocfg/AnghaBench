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
struct samsung_i2s_priv {int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct samsung_i2s_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2s_delete_secondary_device (struct samsung_i2s_priv*) ; 
 int /*<<< orphan*/  i2s_unregister_clock_provider (struct samsung_i2s_priv*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int samsung_i2s_remove(struct platform_device *pdev)
{
	struct samsung_i2s_priv *priv = dev_get_drvdata(&pdev->dev);

	/* The secondary device has no driver data assigned */
	if (!priv)
		return 0;

	pm_runtime_get_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	i2s_unregister_clock_provider(priv);
	i2s_delete_secondary_device(priv);
	clk_disable_unprepare(priv->clk);

	pm_runtime_put_noidle(&pdev->dev);

	return 0;
}