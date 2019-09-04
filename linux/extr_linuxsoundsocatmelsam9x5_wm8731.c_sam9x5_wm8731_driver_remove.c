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
struct snd_soc_card {struct sam9x5_drvdata* drvdata; } ;
struct sam9x5_drvdata {int /*<<< orphan*/  ssc_id; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_ssc_put_audio (int /*<<< orphan*/ ) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 

__attribute__((used)) static int sam9x5_wm8731_driver_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct sam9x5_drvdata *priv = card->drvdata;

	snd_soc_unregister_card(card);
	atmel_ssc_put_audio(priv->ssc_id);

	return 0;
}