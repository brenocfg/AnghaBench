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
struct tegra20_ac97 {int /*<<< orphan*/  clk_ac97; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct tegra20_ac97* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pcm_platform_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra20_ac97_platform_remove(struct platform_device *pdev)
{
	struct tegra20_ac97 *ac97 = dev_get_drvdata(&pdev->dev);

	tegra_pcm_platform_unregister(&pdev->dev);
	snd_soc_unregister_component(&pdev->dev);

	clk_disable_unprepare(ac97->clk_ac97);

	snd_soc_set_ac97_ops(NULL);

	return 0;
}