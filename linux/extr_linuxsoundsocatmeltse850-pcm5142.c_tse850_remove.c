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
struct tse850_priv {int /*<<< orphan*/  ana; } ;
struct snd_soc_card {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct tse850_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 

__attribute__((used)) static int tse850_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct tse850_priv *tse850 = snd_soc_card_get_drvdata(card);

	snd_soc_unregister_card(card);
	regulator_disable(tse850->ana);

	return 0;
}