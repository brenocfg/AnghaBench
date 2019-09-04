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
typedef  int uint32_t ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct jz4740_i2s {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int JZ_AIC_CTRL_ENABLE_CAPTURE ; 
 int JZ_AIC_CTRL_ENABLE_PLAYBACK ; 
 int JZ_AIC_CTRL_ENABLE_RX_DMA ; 
 int JZ_AIC_CTRL_ENABLE_TX_DMA ; 
 int /*<<< orphan*/  JZ_REG_AIC_CTRL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int jz4740_i2s_read (struct jz4740_i2s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_i2s_write (struct jz4740_i2s*,int /*<<< orphan*/ ,int) ; 
 struct jz4740_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int jz4740_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
	struct snd_soc_dai *dai)
{
	struct jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	uint32_t ctrl;
	uint32_t mask;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		mask = JZ_AIC_CTRL_ENABLE_PLAYBACK | JZ_AIC_CTRL_ENABLE_TX_DMA;
	else
		mask = JZ_AIC_CTRL_ENABLE_CAPTURE | JZ_AIC_CTRL_ENABLE_RX_DMA;

	ctrl = jz4740_i2s_read(i2s, JZ_REG_AIC_CTRL);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ctrl |= mask;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ctrl &= ~mask;
		break;
	default:
		return -EINVAL;
	}

	jz4740_i2s_write(i2s, JZ_REG_AIC_CTRL, ctrl);

	return 0;
}