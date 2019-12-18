#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_4__* pcm; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_dmaengine_pcm_config {size_t prealloc_buffer_size; scalar_t__* chan_names; TYPE_1__* pcm_hardware; } ;
struct dmaengine_pcm {int flags; scalar_t__* chan; struct snd_dmaengine_pcm_config* config; } ;
struct device {int dummy; } ;
struct TYPE_8__ {TYPE_3__* streams; } ;
struct TYPE_7__ {TYPE_2__* pcm; struct snd_pcm_substream* substream; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {size_t buffer_bytes_max; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_IRAM ; 
 unsigned int SNDRV_PCM_STREAM_CAPTURE ; 
 unsigned int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_DMAENGINE_PCM_DRV_NAME ; 
 int SND_DMAENGINE_PCM_FLAG_COMPAT ; 
 int SND_DMAENGINE_PCM_FLAG_NO_RESIDUE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 scalar_t__ dma_request_slave_channel (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dmaengine_dma_dev (struct dmaengine_pcm*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  dmaengine_pcm_can_report_residue (struct device*,scalar_t__) ; 
 scalar_t__ dmaengine_pcm_compat_request_channel (struct snd_soc_pcm_runtime*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct dmaengine_pcm* soc_component_to_pcm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  strscpy_pad (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dmaengine_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, SND_DMAENGINE_PCM_DRV_NAME);
	struct dmaengine_pcm *pcm = soc_component_to_pcm(component);
	const struct snd_dmaengine_pcm_config *config = pcm->config;
	struct device *dev = component->dev;
	struct snd_pcm_substream *substream;
	size_t prealloc_buffer_size;
	size_t max_buffer_size;
	unsigned int i;

	if (config && config->prealloc_buffer_size) {
		prealloc_buffer_size = config->prealloc_buffer_size;
		max_buffer_size = config->pcm_hardware->buffer_bytes_max;
	} else {
		prealloc_buffer_size = 512 * 1024;
		max_buffer_size = SIZE_MAX;
	}

	for (i = SNDRV_PCM_STREAM_PLAYBACK; i <= SNDRV_PCM_STREAM_CAPTURE; i++) {
		substream = rtd->pcm->streams[i].substream;
		if (!substream)
			continue;

		if (!pcm->chan[i] && config && config->chan_names[i])
			pcm->chan[i] = dma_request_slave_channel(dev,
				config->chan_names[i]);

		if (!pcm->chan[i] && (pcm->flags & SND_DMAENGINE_PCM_FLAG_COMPAT)) {
			pcm->chan[i] = dmaengine_pcm_compat_request_channel(rtd,
				substream);
		}

		if (!pcm->chan[i]) {
			dev_err(component->dev,
				"Missing dma channel for stream: %d\n", i);
			return -EINVAL;
		}

		snd_pcm_lib_preallocate_pages(substream,
				SNDRV_DMA_TYPE_DEV_IRAM,
				dmaengine_dma_dev(pcm, substream),
				prealloc_buffer_size,
				max_buffer_size);

		if (!dmaengine_pcm_can_report_residue(dev, pcm->chan[i]))
			pcm->flags |= SND_DMAENGINE_PCM_FLAG_NO_RESIDUE;

		if (rtd->pcm->streams[i].pcm->name[0] == '\0') {
			strscpy_pad(rtd->pcm->streams[i].pcm->name,
				    rtd->pcm->streams[i].pcm->id,
				    sizeof(rtd->pcm->streams[i].pcm->name));
		}
	}

	return 0;
}