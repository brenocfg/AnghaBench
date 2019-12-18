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
struct TYPE_2__ {int mode; int start_delay; int data_polarity; int frame_sync_width; int nb_bits_per_slots; int frame_sync_polarity; void* ssp_protocol; } ;
struct sst_data {TYPE_1__ ssp_cmd; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SND_SOC_DAIFMT_DSP_A 131 
#define  SND_SOC_DAIFMT_DSP_B 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 void* SSP_MODE_I2S ; 
 void* SSP_MODE_PCM ; 
 int SSP_PCM_MODE_NETWORK ; 
 int SSP_PCM_MODE_NORMAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct sst_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int sst_get_frame_sync_polarity (struct snd_soc_dai*,unsigned int) ; 
 int sst_get_ssp_mode (struct snd_soc_dai*,unsigned int) ; 

int sst_fill_ssp_config(struct snd_soc_dai *dai, unsigned int fmt)
{
	unsigned int mode;
	int fs_polarity;
	struct sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	mode = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	switch (mode) {
	case SND_SOC_DAIFMT_DSP_B:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_PCM;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NETWORK << 1);
		ctx->ssp_cmd.start_delay = 0;
		ctx->ssp_cmd.data_polarity = 1;
		ctx->ssp_cmd.frame_sync_width = 1;
		break;

	case SND_SOC_DAIFMT_DSP_A:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_PCM;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NETWORK << 1);
		ctx->ssp_cmd.start_delay = 1;
		ctx->ssp_cmd.data_polarity = 1;
		ctx->ssp_cmd.frame_sync_width = 1;
		break;

	case SND_SOC_DAIFMT_I2S:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_I2S;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NORMAL << 1);
		ctx->ssp_cmd.start_delay = 1;
		ctx->ssp_cmd.data_polarity = 0;
		ctx->ssp_cmd.frame_sync_width = ctx->ssp_cmd.nb_bits_per_slots;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_I2S;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NORMAL << 1);
		ctx->ssp_cmd.start_delay = 0;
		ctx->ssp_cmd.data_polarity = 0;
		ctx->ssp_cmd.frame_sync_width = ctx->ssp_cmd.nb_bits_per_slots;
		break;

	default:
		dev_dbg(dai->dev, "using default ssp configs\n");
	}

	fs_polarity = sst_get_frame_sync_polarity(dai, fmt);
	if (fs_polarity < 0)
		return fs_polarity;

	ctx->ssp_cmd.frame_sync_polarity = fs_polarity;

	return 0;
}