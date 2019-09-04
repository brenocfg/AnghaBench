#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__** codec_dais; struct snd_soc_card* card; } ;
struct snd_soc_card {struct glb_pool* drvdata; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct glb_pool {int /*<<< orphan*/  set_lowpass; int /*<<< orphan*/  set_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_2__* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_PLL_EN ; 
 int /*<<< orphan*/  PCM512x_PLL_REF ; 
 int /*<<< orphan*/  PCM512x_RATE_DET_4 ; 
 int PCM512x_SREF_BCK ; 
 int PCM512x_SREF_SCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ glb_mclk ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_allo_piano_dsp_program (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int snd_soc_component_read (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snd_soc_component_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_allo_piano_dac_hw_params(
		struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	unsigned int rate = params_rate(params);
	struct snd_soc_card *card = rtd->card;
	struct glb_pool *glb_ptr = card->drvdata;
	int ret = 0, val = 0, dac;

	for (dac = 0; (glb_mclk && dac < 2); dac++) {
		/* Configure the PLL clock reference for both the Codecs */
		ret = snd_soc_component_read(rtd->codec_dais[dac]->component,
					PCM512x_RATE_DET_4, &val);
		if (ret < 0) {
			dev_err(rtd->codec_dais[dac]->component->dev,
				"Failed to read register PCM512x_RATE_DET_4\n");
			return ret;
		}

		if (val & 0x40) {
			snd_soc_component_write(rtd->codec_dais[dac]->component,
					PCM512x_PLL_REF,
					PCM512x_SREF_BCK);

			dev_info(rtd->codec_dais[dac]->component->dev,
				"Setting BCLK as input clock & Enable PLL\n");
		} else {
			snd_soc_component_write(rtd->codec_dais[dac]->component,
					PCM512x_PLL_EN,
					0x00);

			snd_soc_component_write(rtd->codec_dais[dac]->component,
					PCM512x_PLL_REF,
					PCM512x_SREF_SCK);

			dev_info(rtd->codec_dais[dac]->component->dev,
				"Setting SCLK as input clock & disabled PLL\n");
		}
	}

	ret = snd_allo_piano_dsp_program(rtd, glb_ptr->set_mode, rate,
						glb_ptr->set_lowpass);
	if (ret < 0)
		return ret;

	return ret;
}