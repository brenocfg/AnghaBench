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
struct tegra30_i2s {int /*<<< orphan*/  clk_i2s; int /*<<< orphan*/  playback_fifo_cif; int /*<<< orphan*/  playback_i2s_cif; int /*<<< orphan*/  capture_fifo_cif; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 struct tegra30_i2s* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra30_ahub_free_rx_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra30_ahub_free_tx_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra30_ahub_unset_rx_cif_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra30_i2s_runtime_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pcm_platform_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra30_i2s_platform_remove(struct platform_device *pdev)
{
	struct tegra30_i2s *i2s = dev_get_drvdata(&pdev->dev);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra30_i2s_runtime_suspend(&pdev->dev);

	tegra_pcm_platform_unregister(&pdev->dev);
	snd_soc_unregister_component(&pdev->dev);

	tegra30_ahub_unset_rx_cif_source(i2s->capture_fifo_cif);
	tegra30_ahub_free_rx_fifo(i2s->capture_fifo_cif);

	tegra30_ahub_unset_rx_cif_source(i2s->playback_i2s_cif);
	tegra30_ahub_free_tx_fifo(i2s->playback_fifo_cif);

	clk_put(i2s->clk_i2s);

	return 0;
}