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
struct snd_soc_dai {size_t id; int /*<<< orphan*/  dev; TYPE_3__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {size_t stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct hdac_hda_priv {TYPE_4__* pcm; } ;
struct TYPE_8__ {unsigned int* format_val; } ;
struct TYPE_6__ {unsigned int sig_bits; } ;
struct TYPE_5__ {unsigned int sig_bits; } ;
struct TYPE_7__ {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 unsigned int snd_hdac_calc_stream_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct hdac_hda_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int hdac_hda_dai_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *params,
				  struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct hdac_hda_priv *hda_pvt;
	unsigned int format_val;
	unsigned int maxbps;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		maxbps = dai->driver->playback.sig_bits;
	else
		maxbps = dai->driver->capture.sig_bits;

	hda_pvt = snd_soc_component_get_drvdata(component);
	format_val = snd_hdac_calc_stream_format(params_rate(params),
						 params_channels(params),
						 params_format(params),
						 maxbps,
						 0);
	if (!format_val) {
		dev_err(dai->dev,
			"invalid format_val, rate=%d, ch=%d, format=%d, maxbps=%d\n",
			params_rate(params), params_channels(params),
			params_format(params), maxbps);

		return -EINVAL;
	}

	hda_pvt->pcm[dai->id].format_val[substream->stream] = format_val;
	return 0;
}