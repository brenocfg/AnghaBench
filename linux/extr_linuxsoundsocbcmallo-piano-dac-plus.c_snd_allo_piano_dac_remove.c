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
struct snd_soc_card {int /*<<< orphan*/  drvdata; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_allo_piano_dac ; 
 int /*<<< orphan*/  snd_allo_piano_gpio_mute (int /*<<< orphan*/ *) ; 
 int snd_soc_unregister_card (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_allo_piano_dac_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	kfree(&card->drvdata);
	snd_allo_piano_gpio_mute(&snd_allo_piano_dac);
	return snd_soc_unregister_card(&snd_allo_piano_dac);
}