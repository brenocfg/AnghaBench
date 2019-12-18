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
typedef  int /*<<< orphan*/  u32 ;
struct xlnx_pcm_stream_param {scalar_t__ mmio; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct xlnx_pcm_stream_param* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CTRL_DMA_EN_MASK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ XLNX_AUD_CTRL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xlnx_formatter_pcm_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
	u32 val;
	struct xlnx_pcm_stream_param *stream_data =
			substream->runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		val = readl(stream_data->mmio + XLNX_AUD_CTRL);
		val |= AUD_CTRL_DMA_EN_MASK;
		writel(val, stream_data->mmio + XLNX_AUD_CTRL);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		val = readl(stream_data->mmio + XLNX_AUD_CTRL);
		val &= ~AUD_CTRL_DMA_EN_MASK;
		writel(val, stream_data->mmio + XLNX_AUD_CTRL);
		break;
	}

	return 0;
}