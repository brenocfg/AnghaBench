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
struct snd_soc_card {int /*<<< orphan*/ * dev; int /*<<< orphan*/  name; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int soc_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	/*
	 * no card, so machine driver should be registering card
	 * we should not be here in that case so ret error
	 */
	if (!card)
		return -EINVAL;

	dev_warn(&pdev->dev,
		 "ASoC: machine %s should use snd_soc_register_card()\n",
		 card->name);

	/* Bodge while we unpick instantiation */
	card->dev = &pdev->dev;

	return snd_soc_register_card(card);
}