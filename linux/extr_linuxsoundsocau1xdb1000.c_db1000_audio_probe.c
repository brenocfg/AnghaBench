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
struct snd_soc_card {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct snd_soc_card db1000_ac97 ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 

__attribute__((used)) static int db1000_audio_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &db1000_ac97;
	card->dev = &pdev->dev;
	return devm_snd_soc_register_card(&pdev->dev, card);
}