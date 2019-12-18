#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int info; } ;
struct xen_snd_front_pcm_stream_info {size_t index; TYPE_7__* evt_pair; struct xen_snd_front_info* front_info; TYPE_3__ pcm_hw; } ;
struct xen_snd_front_pcm_instance_info {TYPE_1__* card_info; } ;
struct xen_snd_front_info {TYPE_7__* evt_pairs; TYPE_2__* xb_dev; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {TYPE_3__ hw; } ;
struct device {int dummy; } ;
struct TYPE_11__ {struct snd_pcm_substream* substream; } ;
struct TYPE_12__ {TYPE_4__ evt; } ;
struct TYPE_13__ {TYPE_5__ u; } ;
struct TYPE_14__ {TYPE_6__ evt; } ;
struct TYPE_9__ {struct device dev; } ;
struct TYPE_8__ {struct xen_snd_front_info* front_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int SNDRV_PCM_INFO_BATCH ; 
 int SNDRV_PCM_INFO_DOUBLE ; 
 int SNDRV_PCM_INFO_INTERLEAVED ; 
 int SNDRV_PCM_INFO_MMAP ; 
 int SNDRV_PCM_INFO_MMAP_VALID ; 
 int SNDRV_PCM_INFO_NONINTERLEAVED ; 
 int SNDRV_PCM_INFO_PAUSE ; 
 int SNDRV_PCM_INFO_RESUME ; 
 int /*<<< orphan*/  alsa_hw_rule ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xen_snd_front_pcm_stream_info*,int /*<<< orphan*/ ,int) ; 
 struct xen_snd_front_pcm_instance_info* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stream_clear (struct xen_snd_front_pcm_stream_info*) ; 
 struct xen_snd_front_pcm_stream_info* stream_get (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  xen_snd_front_evtchnl_pair_set_connected (TYPE_7__*,int) ; 

__attribute__((used)) static int alsa_open(struct snd_pcm_substream *substream)
{
	struct xen_snd_front_pcm_instance_info *pcm_instance =
			snd_pcm_substream_chip(substream);
	struct xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct xen_snd_front_info *front_info =
			pcm_instance->card_info->front_info;
	struct device *dev = &front_info->xb_dev->dev;
	int ret;

	/*
	 * Return our HW properties: override defaults with those configured
	 * via XenStore.
	 */
	runtime->hw = stream->pcm_hw;
	runtime->hw.info &= ~(SNDRV_PCM_INFO_MMAP |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_DOUBLE |
			      SNDRV_PCM_INFO_BATCH |
			      SNDRV_PCM_INFO_NONINTERLEAVED |
			      SNDRV_PCM_INFO_RESUME |
			      SNDRV_PCM_INFO_PAUSE);
	runtime->hw.info |= SNDRV_PCM_INFO_INTERLEAVED;

	stream->evt_pair = &front_info->evt_pairs[stream->index];

	stream->front_info = front_info;

	stream->evt_pair->evt.u.evt.substream = substream;

	stream_clear(stream);

	xen_snd_front_evtchnl_pair_set_connected(stream->evt_pair, true);

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_FORMAT,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_FORMAT, -1);
	if (ret) {
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_FORMAT\n");
		return ret;
	}

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (ret) {
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_RATE\n");
		return ret;
	}

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	if (ret) {
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_CHANNELS\n");
		return ret;
	}

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	if (ret) {
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_PERIOD_SIZE\n");
		return ret;
	}

	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, -1);
	if (ret) {
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_BUFFER_SIZE\n");
		return ret;
	}

	return 0;
}