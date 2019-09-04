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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct omap_dmic {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  omap_dmic_start (struct omap_dmic*) ; 
 int /*<<< orphan*/  omap_dmic_stop (struct omap_dmic*) ; 
 struct omap_dmic* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_dmic_dai_trigger(struct snd_pcm_substream *substream,
				  int cmd, struct snd_soc_dai *dai)
{
	struct omap_dmic *dmic = snd_soc_dai_get_drvdata(dai);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		omap_dmic_start(dmic);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		omap_dmic_stop(dmic);
		break;
	default:
		break;
	}

	return 0;
}