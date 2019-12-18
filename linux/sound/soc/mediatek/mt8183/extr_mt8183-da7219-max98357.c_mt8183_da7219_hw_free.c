#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  dev; struct snd_soc_dai** codec_dais; } ;
struct snd_soc_dai {TYPE_1__* component; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_SYSCLK_MCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mt8183_da7219_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int ret = 0, j;

	for (j = 0; j < rtd->num_codecs; j++) {
		struct snd_soc_dai *codec_dai = rtd->codec_dais[j];

		if (!strcmp(codec_dai->component->name, "da7219.5-001a")) {
			ret = snd_soc_dai_set_pll(codec_dai,
						  0, DA7219_SYSCLK_MCLK, 0, 0);
			if (ret < 0) {
				dev_err(rtd->dev, "failed to stop PLL: %d\n",
					ret);
				break;
			}
		}
	}

	return ret;
}