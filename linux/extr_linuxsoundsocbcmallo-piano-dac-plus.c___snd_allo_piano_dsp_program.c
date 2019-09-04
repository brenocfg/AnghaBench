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
struct snd_soc_pcm_runtime {int num_codecs; struct snd_soc_card* card; TYPE_1__** codec_dais; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; struct glb_pool* drvdata; } ;
struct glb_pool {unsigned int set_lowpass; unsigned int set_mode; unsigned int set_rate; int /*<<< orphan*/  dsp_page_number; scalar_t__ dual_mode; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;
struct dsp_code {scalar_t__ offset; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  firmware_name ;
struct TYPE_2__ {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 scalar_t__ PCM512x_MUTE ; 
 scalar_t__ PCM512x_PAGE_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_DAC_MUTE ; 
 int /*<<< orphan*/  P_DAC_UNMUTE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int,unsigned int,...) ; 

__attribute__((used)) static int __snd_allo_piano_dsp_program(struct snd_soc_pcm_runtime *rtd,
		unsigned int mode, unsigned int rate, unsigned int lowpass)
{
	const struct firmware *fw;
	struct snd_soc_card *card = rtd->card;
	struct glb_pool *glb_ptr = card->drvdata;
	char firmware_name[60];
	int ret = 0, dac = 0;

	if (rate <= 46000)
		rate = 44100;
	else if (rate <= 68000)
		rate = 48000;
	else if (rate <= 92000)
		rate = 88200;
	else if (rate <= 136000)
		rate = 96000;
	else if (rate <= 184000)
		rate = 176400;
	else
		rate = 192000;

	if (lowpass > 14)
		glb_ptr->set_lowpass = lowpass = 0;

	if (mode > 3)
		glb_ptr->set_mode = mode = 0;

	if (mode > 0)
		glb_ptr->dual_mode = 0;

	/* same configuration loaded */
	if ((rate == glb_ptr->set_rate) && (lowpass == glb_ptr->set_lowpass)
			&& (mode == glb_ptr->set_mode))
		return 0;

	switch (mode) {
	case 0: /* None */
		return 1;

	case 1: /* 2.0 */
		snd_soc_component_write(rtd->codec_dais[0]->component,
				PCM512x_MUTE, P_DAC_UNMUTE);
		snd_soc_component_write(rtd->codec_dais[1]->component,
				PCM512x_MUTE, P_DAC_MUTE);
		glb_ptr->set_rate = rate;
		glb_ptr->set_mode = mode;
		glb_ptr->set_lowpass = lowpass;
		return 1;

	default:
		snd_soc_component_write(rtd->codec_dais[0]->component,
				PCM512x_MUTE, P_DAC_UNMUTE);
		snd_soc_component_write(rtd->codec_dais[1]->component,
				PCM512x_MUTE, P_DAC_UNMUTE);
	}

	for (dac = 0; dac < rtd->num_codecs; dac++) {
		struct dsp_code *dsp_code_read;
		int i = 1;

		if (dac == 0) { /* high */
			snprintf(firmware_name, sizeof(firmware_name),
				"allo/piano/2.2/allo-piano-dsp-%d-%d-%d.bin",
				rate, ((lowpass * 10) + 60), dac);
		} else { /* low */
			snprintf(firmware_name, sizeof(firmware_name),
				"allo/piano/2.%d/allo-piano-dsp-%d-%d-%d.bin",
				(mode - 1), rate, ((lowpass * 10) + 60), dac);
		}

		dev_info(rtd->card->dev, "Dsp Firmware File Name: %s\n",
				firmware_name);

		ret = request_firmware(&fw, firmware_name, rtd->card->dev);
		if (ret < 0) {
			dev_err(rtd->card->dev,
				"Error: Allo Piano Firmware %s missing. %d\n",
				firmware_name, ret);
			goto err;
		}

		while (i < (fw->size - 1)) {
			dsp_code_read = (struct dsp_code *)&fw->data[i];

			if (dsp_code_read->offset == 0) {
				glb_ptr->dsp_page_number = dsp_code_read->val;
				ret = snd_soc_component_write(rtd->codec_dais[dac]->component,
						PCM512x_PAGE_BASE(0),
						dsp_code_read->val);

			} else if (dsp_code_read->offset != 0) {
				ret = snd_soc_component_write(rtd->codec_dais[dac]->component,
					(PCM512x_PAGE_BASE(
						glb_ptr->dsp_page_number) +
					dsp_code_read->offset),
					dsp_code_read->val);
			}
			if (ret < 0) {
				dev_err(rtd->card->dev,
					"Failed to write Register: %d\n", ret);
				release_firmware(fw);
				goto err;
			}
			i = i + 3;
		}
		release_firmware(fw);
	}
	glb_ptr->set_rate = rate;
	glb_ptr->set_mode = mode;
	glb_ptr->set_lowpass = lowpass;
	return 1;

err:
	return ret;
}