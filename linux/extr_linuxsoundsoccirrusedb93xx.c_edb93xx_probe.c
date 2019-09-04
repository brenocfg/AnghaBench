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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ep93xx_i2s_acquire () ; 
 int /*<<< orphan*/  ep93xx_i2s_release () ; 
 struct snd_soc_card snd_soc_edb93xx ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int edb93xx_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_edb93xx;
	int ret;

	ret = ep93xx_i2s_acquire();
	if (ret)
		return ret;

	card->dev = &pdev->dev;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		ep93xx_i2s_release();
	}

	return ret;
}