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
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct snd_soc_card ams_delta_audio_card ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handset_mute ; 
 int /*<<< orphan*/  handsfree_mute ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int ams_delta_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &ams_delta_audio_card;
	int ret;

	card->dev = &pdev->dev;

	handset_mute = devm_gpiod_get(card->dev, "handset_mute",
				      GPIOD_OUT_HIGH);
	if (IS_ERR(handset_mute))
		return PTR_ERR(handset_mute);

	handsfree_mute = devm_gpiod_get(card->dev, "handsfree_mute",
					GPIOD_OUT_HIGH);
	if (IS_ERR(handsfree_mute))
		return PTR_ERR(handsfree_mute);

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		card->dev = NULL;
		return ret;
	}
	return 0;
}