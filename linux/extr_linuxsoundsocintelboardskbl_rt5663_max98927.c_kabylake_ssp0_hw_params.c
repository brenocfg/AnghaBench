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
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXIM_DEV0_NAME ; 
 int /*<<< orphan*/  MAXIM_DEV1_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_dai_set_tdm_slot (struct snd_soc_dai*,int,int,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kabylake_ssp0_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int ret = 0, j;

	for (j = 0; j < rtd->num_codecs; j++) {
		struct snd_soc_dai *codec_dai = rtd->codec_dais[j];

		if (!strcmp(codec_dai->component->name, MAXIM_DEV0_NAME)) {
			/*
			 * Use channel 4 and 5 for the first amp
			 */
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x30, 3, 8, 16);
			if (ret < 0) {
				dev_err(rtd->dev, "set TDM slot err:%d\n", ret);
				return ret;
			}
		}
		if (!strcmp(codec_dai->component->name, MAXIM_DEV1_NAME)) {
			/*
			 * Use channel 6 and 7 for the second amp
			 */
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0xC0, 3, 8, 16);
			if (ret < 0) {
				dev_err(rtd->dev, "set TDM slot err:%d\n", ret);
				return ret;
			}
		}
	}
	return ret;
}