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
struct zx_i2s_info {int /*<<< orphan*/  reg_base; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct zx_i2s_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_i2s_rx_dma_en (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zx_i2s_rx_en (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zx_i2s_tx_dma_en (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zx_i2s_tx_en (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zx_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			  struct snd_soc_dai *dai)
{
	struct zx_i2s_info *zx_i2s = dev_get_drvdata(dai->dev);
	int capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (capture)
			zx_i2s_rx_dma_en(zx_i2s->reg_base, true);
		else
			zx_i2s_tx_dma_en(zx_i2s->reg_base, true);
	/* fall thru */
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (capture)
			zx_i2s_rx_en(zx_i2s->reg_base, true);
		else
			zx_i2s_tx_en(zx_i2s->reg_base, true);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		if (capture)
			zx_i2s_rx_dma_en(zx_i2s->reg_base, false);
		else
			zx_i2s_tx_dma_en(zx_i2s->reg_base, false);
	/* fall thru */
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (capture)
			zx_i2s_rx_en(zx_i2s->reg_base, false);
		else
			zx_i2s_tx_en(zx_i2s->reg_base, false);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}