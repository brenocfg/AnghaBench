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
struct TYPE_6__ {int num_ch; int packet_mode; int left_align; int val_bit; int dp_modei; int set; int /*<<< orphan*/  layout; } ;
union aud_cfg {int /*<<< orphan*/  regval; TYPE_3__ regx; } ;
struct TYPE_4__ {scalar_t__ aud_delay; int /*<<< orphan*/  dma_fifo_watermark; int /*<<< orphan*/  audio_fifo_watermark; } ;
union aud_buf_config {int /*<<< orphan*/  regval; TYPE_1__ regx; } ;
typedef  int u8 ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct snd_intelhad {union aud_cfg aud_config; scalar_t__ dp_output; } ;
struct TYPE_5__ {int channels; scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_BUF_CONFIG ; 
 int /*<<< orphan*/  AUD_CONFIG ; 
 int /*<<< orphan*/  DMA_FIFO_THRESHOLD ; 
 int /*<<< orphan*/  FIFO_THRESHOLD ; 
 int /*<<< orphan*/  LAYOUT0 ; 
 int /*<<< orphan*/  LAYOUT1 ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16_LE ; 
 scalar_t__ SNDRV_PCM_FORMAT_S32_LE ; 
 int /*<<< orphan*/  had_prog_status_reg (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int had_init_audio_ctrl(struct snd_pcm_substream *substream,
			       struct snd_intelhad *intelhaddata)
{
	union aud_cfg cfg_val = {.regval = 0};
	union aud_buf_config buf_cfg = {.regval = 0};
	u8 channels;

	had_prog_status_reg(substream, intelhaddata);

	buf_cfg.regx.audio_fifo_watermark = FIFO_THRESHOLD;
	buf_cfg.regx.dma_fifo_watermark = DMA_FIFO_THRESHOLD;
	buf_cfg.regx.aud_delay = 0;
	had_write_register(intelhaddata, AUD_BUF_CONFIG, buf_cfg.regval);

	channels = substream->runtime->channels;
	cfg_val.regx.num_ch = channels - 2;
	if (channels <= 2)
		cfg_val.regx.layout = LAYOUT0;
	else
		cfg_val.regx.layout = LAYOUT1;

	if (substream->runtime->format == SNDRV_PCM_FORMAT_S16_LE)
		cfg_val.regx.packet_mode = 1;

	if (substream->runtime->format == SNDRV_PCM_FORMAT_S32_LE)
		cfg_val.regx.left_align = 1;

	cfg_val.regx.val_bit = 1;

	/* fix up the DP bits */
	if (intelhaddata->dp_output) {
		cfg_val.regx.dp_modei = 1;
		cfg_val.regx.set = 1;
	}

	had_write_register(intelhaddata, AUD_CONFIG, cfg_val.regval);
	intelhaddata->aud_config = cfg_val;
	return 0;
}