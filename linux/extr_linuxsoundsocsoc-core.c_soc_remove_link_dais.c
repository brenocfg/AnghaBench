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
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  cpu_dai; int /*<<< orphan*/ * codec_dais; scalar_t__ dev_registered; int /*<<< orphan*/  dev; } ;
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_remove_dai (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void soc_remove_link_dais(struct snd_soc_card *card,
		struct snd_soc_pcm_runtime *rtd, int order)
{
	int i;

	/* unregister the rtd device */
	if (rtd->dev_registered) {
		device_unregister(rtd->dev);
		rtd->dev_registered = 0;
	}

	/* remove the CODEC DAI */
	for (i = 0; i < rtd->num_codecs; i++)
		soc_remove_dai(rtd->codec_dais[i], order);

	soc_remove_dai(rtd->cpu_dai, order);
}