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
struct snd_card {struct azx* private_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct azx {scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_stop_chip (struct azx*) ; 
 struct snd_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hda_tegra_shutdown(struct platform_device *pdev)
{
	struct snd_card *card = dev_get_drvdata(&pdev->dev);
	struct azx *chip;

	if (!card)
		return;
	chip = card->private_data;
	if (chip && chip->running)
		azx_stop_chip(chip);
}