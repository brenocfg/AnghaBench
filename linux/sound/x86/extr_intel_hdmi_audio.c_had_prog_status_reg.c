#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wrd_len; int /*<<< orphan*/  max_wrd_len; } ;
union aud_ch_status_1 {int /*<<< orphan*/  regval; TYPE_3__ regx; } ;
struct TYPE_4__ {int lpcm_id; int clk_acc; int /*<<< orphan*/  samp_freq; } ;
union aud_ch_status_0 {int /*<<< orphan*/  regval; TYPE_1__ regx; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct snd_intelhad {int aes_bits; } ;
struct TYPE_5__ {int rate; int format; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CH_STATUS_0 ; 
 int /*<<< orphan*/  AUD_CH_STATUS_1 ; 
#define  AUD_SAMPLE_RATE_176_4 137 
#define  AUD_SAMPLE_RATE_192 136 
#define  AUD_SAMPLE_RATE_32 135 
#define  AUD_SAMPLE_RATE_44_1 134 
#define  AUD_SAMPLE_RATE_48 133 
#define  AUD_SAMPLE_RATE_88_2 132 
#define  AUD_SAMPLE_RATE_96 131 
 int /*<<< orphan*/  CH_STATUS_MAP_176KHZ ; 
 int /*<<< orphan*/  CH_STATUS_MAP_192KHZ ; 
 int /*<<< orphan*/  CH_STATUS_MAP_32KHZ ; 
 int /*<<< orphan*/  CH_STATUS_MAP_44KHZ ; 
 int /*<<< orphan*/  CH_STATUS_MAP_48KHZ ; 
 int /*<<< orphan*/  CH_STATUS_MAP_88KHZ ; 
 int /*<<< orphan*/  CH_STATUS_MAP_96KHZ ; 
 int EINVAL ; 
 int IEC958_AES0_NONAUDIO ; 
 int IEC958_AES3_CON_CLOCK ; 
 int /*<<< orphan*/  MAX_SMPL_WIDTH_20 ; 
 int /*<<< orphan*/  MAX_SMPL_WIDTH_24 ; 
 int /*<<< orphan*/  SMPL_WIDTH_16BITS ; 
 int /*<<< orphan*/  SMPL_WIDTH_24BITS ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int had_prog_status_reg(struct snd_pcm_substream *substream,
			struct snd_intelhad *intelhaddata)
{
	union aud_ch_status_0 ch_stat0 = {.regval = 0};
	union aud_ch_status_1 ch_stat1 = {.regval = 0};

	ch_stat0.regx.lpcm_id = (intelhaddata->aes_bits &
					  IEC958_AES0_NONAUDIO) >> 1;
	ch_stat0.regx.clk_acc = (intelhaddata->aes_bits &
					  IEC958_AES3_CON_CLOCK) >> 4;

	switch (substream->runtime->rate) {
	case AUD_SAMPLE_RATE_32:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_32KHZ;
		break;

	case AUD_SAMPLE_RATE_44_1:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_44KHZ;
		break;
	case AUD_SAMPLE_RATE_48:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_48KHZ;
		break;
	case AUD_SAMPLE_RATE_88_2:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_88KHZ;
		break;
	case AUD_SAMPLE_RATE_96:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_96KHZ;
		break;
	case AUD_SAMPLE_RATE_176_4:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_176KHZ;
		break;
	case AUD_SAMPLE_RATE_192:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_192KHZ;
		break;

	default:
		/* control should never come here */
		return -EINVAL;
	}

	had_write_register(intelhaddata,
			   AUD_CH_STATUS_0, ch_stat0.regval);

	switch (substream->runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		ch_stat1.regx.max_wrd_len = MAX_SMPL_WIDTH_20;
		ch_stat1.regx.wrd_len = SMPL_WIDTH_16BITS;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
	case SNDRV_PCM_FORMAT_S32_LE:
		ch_stat1.regx.max_wrd_len = MAX_SMPL_WIDTH_24;
		ch_stat1.regx.wrd_len = SMPL_WIDTH_24BITS;
		break;
	default:
		return -EINVAL;
	}

	had_write_register(intelhaddata,
			   AUD_CH_STATUS_1, ch_stat1.regval);
	return 0;
}