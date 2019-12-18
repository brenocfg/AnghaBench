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
struct snd_soc_card {struct snd_soc_card* dai_link; } ;
struct sdm845_snd_data {struct sdm845_snd_data* dai_link; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct snd_soc_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_soc_card*) ; 
 struct snd_soc_card* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 

__attribute__((used)) static int sdm845_snd_platform_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = dev_get_drvdata(&pdev->dev);
	struct sdm845_snd_data *data = snd_soc_card_get_drvdata(card);

	snd_soc_unregister_card(card);
	kfree(card->dai_link);
	kfree(data);
	kfree(card);
	return 0;
}