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
struct sprd_pcm_dma_private {int hw_chan; struct sprd_pcm_dma_data* data; } ;
struct sprd_pcm_dma_data {int /*<<< orphan*/  chan; int /*<<< orphan*/  cookie; int /*<<< orphan*/  desc; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; TYPE_1__* runtime; } ;
struct TYPE_2__ {struct sprd_pcm_dma_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct sprd_pcm_dma_private *dma_private =
		substream->runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	int ret = 0, i;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		for (i = 0; i < dma_private->hw_chan; i++) {
			struct sprd_pcm_dma_data *data = &dma_private->data[i];

			if (!data->desc)
				continue;

			data->cookie = dmaengine_submit(data->desc);
			ret = dma_submit_error(data->cookie);
			if (ret) {
				dev_err(component->dev,
					"failed to submit dma request: %d\n",
					ret);
				return ret;
			}

			dma_async_issue_pending(data->chan);
		}

		break;
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		for (i = 0; i < dma_private->hw_chan; i++) {
			struct sprd_pcm_dma_data *data = &dma_private->data[i];

			if (data->chan)
				dmaengine_resume(data->chan);
		}

		break;
	case SNDRV_PCM_TRIGGER_STOP:
		for (i = 0; i < dma_private->hw_chan; i++) {
			struct sprd_pcm_dma_data *data = &dma_private->data[i];

			if (data->chan)
				dmaengine_terminate_async(data->chan);
		}

		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		for (i = 0; i < dma_private->hw_chan; i++) {
			struct sprd_pcm_dma_data *data = &dma_private->data[i];

			if (data->chan)
				dmaengine_pause(data->chan);
		}

		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}