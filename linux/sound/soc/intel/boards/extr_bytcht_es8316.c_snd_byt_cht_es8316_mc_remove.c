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
struct snd_soc_card {int dummy; } ;
struct platform_device {int dummy; } ;
struct byt_cht_es8316_private {int /*<<< orphan*/  speaker_en_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_put (int /*<<< orphan*/ ) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 struct byt_cht_es8316_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int snd_byt_cht_es8316_mc_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct byt_cht_es8316_private *priv = snd_soc_card_get_drvdata(card);

	gpiod_put(priv->speaker_en_gpio);
	return 0;
}