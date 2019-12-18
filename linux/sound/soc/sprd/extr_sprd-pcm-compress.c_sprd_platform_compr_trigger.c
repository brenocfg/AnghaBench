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
struct sprd_compr_stream {int num_channels; int /*<<< orphan*/  received_total; TYPE_1__* compr_ops; struct sprd_compr_dma* dma; int /*<<< orphan*/  received_stage1; int /*<<< orphan*/  received_stage0; int /*<<< orphan*/  stage1_pointer; int /*<<< orphan*/  copied_total; } ;
struct sprd_compr_dma {int /*<<< orphan*/  chan; int /*<<< orphan*/  cookie; int /*<<< orphan*/  desc; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_compr_stream {int direction; struct snd_soc_pcm_runtime* private_data; struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct sprd_compr_stream* private_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* start ) (int) ;int (* stop ) (int) ;int (* pause ) (int) ;int (* pause_release ) (int) ;int (* drain ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 135 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 134 
#define  SNDRV_PCM_TRIGGER_RESUME 133 
#define  SNDRV_PCM_TRIGGER_START 132 
#define  SNDRV_PCM_TRIGGER_STOP 131 
#define  SNDRV_PCM_TRIGGER_SUSPEND 130 
 int SND_COMPRESS_PLAYBACK ; 
#define  SND_COMPR_TRIGGER_DRAIN 129 
#define  SND_COMPR_TRIGGER_PARTIAL_DRAIN 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 
 int stub4 (int) ; 
 int stub5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_platform_compr_trigger(struct snd_compr_stream *cstream,
				       int cmd)
{
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sprd_compr_stream *stream = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct device *dev = component->dev;
	int channels = stream->num_channels, ret = 0, i;
	int stream_id = cstream->direction;

	if (cstream->direction != SND_COMPRESS_PLAYBACK) {
		dev_err(dev, "unsupported compress direction\n");
		return -EINVAL;
	}

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		for (i = channels - 1; i >= 0; i--) {
			struct sprd_compr_dma *dma = &stream->dma[i];

			if (!dma->desc)
				continue;

			dma->cookie = dmaengine_submit(dma->desc);
			ret = dma_submit_error(dma->cookie);
			if (ret) {
				dev_err(dev, "failed to submit request: %d\n",
					ret);
				return ret;
			}
		}

		for (i = channels - 1; i >= 0; i--) {
			struct sprd_compr_dma *dma = &stream->dma[i];

			if (dma->chan)
				dma_async_issue_pending(dma->chan);
		}

		ret = stream->compr_ops->start(stream_id);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		for (i = channels - 1; i >= 0; i--) {
			struct sprd_compr_dma *dma = &stream->dma[i];

			if (dma->chan)
				dmaengine_terminate_async(dma->chan);
		}

		stream->copied_total = 0;
		stream->stage1_pointer  = 0;
		stream->received_total = 0;
		stream->received_stage0 = 0;
		stream->received_stage1 = 0;

		ret = stream->compr_ops->stop(stream_id);
		break;

	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		for (i = channels - 1; i >= 0; i--) {
			struct sprd_compr_dma *dma = &stream->dma[i];

			if (dma->chan)
				dmaengine_pause(dma->chan);
		}

		ret = stream->compr_ops->pause(stream_id);
		break;

	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		for (i = channels - 1; i >= 0; i--) {
			struct sprd_compr_dma *dma = &stream->dma[i];

			if (dma->chan)
				dmaengine_resume(dma->chan);
		}

		ret = stream->compr_ops->pause_release(stream_id);
		break;

	case SND_COMPR_TRIGGER_PARTIAL_DRAIN:
	case SND_COMPR_TRIGGER_DRAIN:
		ret = stream->compr_ops->drain(stream->received_total);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}