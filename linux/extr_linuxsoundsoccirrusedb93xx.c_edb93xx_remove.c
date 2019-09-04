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

/* Variables and functions */
 int /*<<< orphan*/  ep93xx_i2s_release () ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 

__attribute__((used)) static int edb93xx_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	snd_soc_unregister_card(card);
	ep93xx_i2s_release();

	return 0;
}