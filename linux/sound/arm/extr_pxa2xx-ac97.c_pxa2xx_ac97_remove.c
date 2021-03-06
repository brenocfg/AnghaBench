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
struct snd_card {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct snd_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa2xx_ac97_hw_remove (struct platform_device*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

__attribute__((used)) static int pxa2xx_ac97_remove(struct platform_device *dev)
{
	struct snd_card *card = platform_get_drvdata(dev);

	if (card) {
		snd_card_free(card);
		pxa2xx_ac97_hw_remove(dev);
	}

	return 0;
}