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
typedef  int u64 ;
typedef  void* u32 ;
struct TYPE_14__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_13__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_12__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_11__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct xensnd_query_hw_param {TYPE_7__ period; TYPE_6__ buffer; TYPE_5__ channels; TYPE_4__ rates; int /*<<< orphan*/  formats; } ;
struct xen_snd_front_pcm_stream_info {TYPE_3__* evt_pair; TYPE_2__* front_info; } ;
struct snd_pcm_hw_rule {struct xen_snd_front_pcm_stream_info* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {void** bits; } ;
struct snd_interval {int integer; int /*<<< orphan*/  max; int /*<<< orphan*/  min; scalar_t__ openmax; scalar_t__ openmin; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  req; } ;
struct TYPE_9__ {TYPE_1__* xb_dev; } ;
struct TYPE_8__ {struct device dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int snd_mask_refine (struct snd_mask*,struct snd_mask*) ; 
 int to_alsa_formats_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_sndif_formats_mask (int) ; 
 int xen_snd_front_stream_query_hw_param (int /*<<< orphan*/ *,struct xensnd_query_hw_param*,struct xensnd_query_hw_param*) ; 

__attribute__((used)) static int alsa_hw_rule(struct snd_pcm_hw_params *params,
			struct snd_pcm_hw_rule *rule)
{
	struct xen_snd_front_pcm_stream_info *stream = rule->private;
	struct device *dev = &stream->front_info->xb_dev->dev;
	struct snd_mask *formats =
			hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	struct snd_interval *rates =
			hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval *channels =
			hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval *period =
			hw_param_interval(params,
					  SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
	struct snd_interval *buffer =
			hw_param_interval(params,
					  SNDRV_PCM_HW_PARAM_BUFFER_SIZE);
	struct xensnd_query_hw_param req;
	struct xensnd_query_hw_param resp;
	struct snd_interval interval;
	struct snd_mask mask;
	u64 sndif_formats;
	int changed, ret;

	/* Collect all the values we need for the query. */

	req.formats = to_sndif_formats_mask((u64)formats->bits[0] |
					    (u64)(formats->bits[1]) << 32);

	req.rates.min = rates->min;
	req.rates.max = rates->max;

	req.channels.min = channels->min;
	req.channels.max = channels->max;

	req.buffer.min = buffer->min;
	req.buffer.max = buffer->max;

	req.period.min = period->min;
	req.period.max = period->max;

	ret = xen_snd_front_stream_query_hw_param(&stream->evt_pair->req,
						  &req, &resp);
	if (ret < 0) {
		/* Check if this is due to backend communication error. */
		if (ret == -EIO || ret == -ETIMEDOUT)
			dev_err(dev, "Failed to query ALSA HW parameters\n");
		return ret;
	}

	/* Refine HW parameters after the query. */
	changed  = 0;

	sndif_formats = to_alsa_formats_mask(resp.formats);
	snd_mask_none(&mask);
	mask.bits[0] = (u32)sndif_formats;
	mask.bits[1] = (u32)(sndif_formats >> 32);
	ret = snd_mask_refine(formats, &mask);
	if (ret < 0)
		return ret;
	changed |= ret;

	interval.openmin = 0;
	interval.openmax = 0;
	interval.integer = 1;

	interval.min = resp.rates.min;
	interval.max = resp.rates.max;
	ret = snd_interval_refine(rates, &interval);
	if (ret < 0)
		return ret;
	changed |= ret;

	interval.min = resp.channels.min;
	interval.max = resp.channels.max;
	ret = snd_interval_refine(channels, &interval);
	if (ret < 0)
		return ret;
	changed |= ret;

	interval.min = resp.buffer.min;
	interval.max = resp.buffer.max;
	ret = snd_interval_refine(buffer, &interval);
	if (ret < 0)
		return ret;
	changed |= ret;

	interval.min = resp.period.min;
	interval.max = resp.period.max;
	ret = snd_interval_refine(period, &interval);
	if (ret < 0)
		return ret;
	changed |= ret;

	return changed;
}