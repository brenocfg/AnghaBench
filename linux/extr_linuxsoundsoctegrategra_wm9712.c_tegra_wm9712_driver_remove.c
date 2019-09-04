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
struct tegra_wm9712 {int /*<<< orphan*/  codec; int /*<<< orphan*/  util_data; } ;
struct snd_soc_card {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 struct tegra_wm9712* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 
 int /*<<< orphan*/  tegra_asoc_utils_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_wm9712_driver_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct tegra_wm9712 *machine = snd_soc_card_get_drvdata(card);

	snd_soc_unregister_card(card);

	tegra_asoc_utils_fini(&machine->util_data);

	platform_device_unregister(machine->codec);

	return 0;
}