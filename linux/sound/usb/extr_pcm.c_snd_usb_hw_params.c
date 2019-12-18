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
struct snd_usb_substream {int need_setup_ep; TYPE_3__* stream; int /*<<< orphan*/  altset_idx; int /*<<< orphan*/  interface; int /*<<< orphan*/  channels; int /*<<< orphan*/  cur_rate; int /*<<< orphan*/  pcm_format; TYPE_2__* dev; int /*<<< orphan*/  buffer_periods; int /*<<< orphan*/  period_frames; int /*<<< orphan*/  period_bytes; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct audioformat {int /*<<< orphan*/  altset_idx; int /*<<< orphan*/  iface; } ;
struct TYPE_6__ {int /*<<< orphan*/  chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct snd_usb_substream* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UAC3_PD_STATE_D0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct audioformat* find_format (struct snd_usb_substream*) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_size (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_periods (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int set_format (struct snd_usb_substream*,struct audioformat*) ; 
 int snd_media_start_pipeline (struct snd_usb_substream*) ; 
 int /*<<< orphan*/  snd_media_stop_pipeline (struct snd_usb_substream*) ; 
 int snd_pcm_lib_alloc_vmalloc_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int snd_usb_lock_shutdown (int /*<<< orphan*/ ) ; 
 int snd_usb_pcm_change_state (struct snd_usb_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_usb_use_vmalloc ; 

__attribute__((used)) static int snd_usb_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *hw_params)
{
	struct snd_usb_substream *subs = substream->runtime->private_data;
	struct audioformat *fmt;
	int ret;

	ret = snd_media_start_pipeline(subs);
	if (ret)
		return ret;

	if (snd_usb_use_vmalloc)
		ret = snd_pcm_lib_alloc_vmalloc_buffer(substream,
						       params_buffer_bytes(hw_params));
	else
		ret = snd_pcm_lib_malloc_pages(substream,
					       params_buffer_bytes(hw_params));
	if (ret < 0)
		goto stop_pipeline;

	subs->pcm_format = params_format(hw_params);
	subs->period_bytes = params_period_bytes(hw_params);
	subs->period_frames = params_period_size(hw_params);
	subs->buffer_periods = params_periods(hw_params);
	subs->channels = params_channels(hw_params);
	subs->cur_rate = params_rate(hw_params);

	fmt = find_format(subs);
	if (!fmt) {
		dev_dbg(&subs->dev->dev,
			"cannot set format: format = %#x, rate = %d, channels = %d\n",
			   subs->pcm_format, subs->cur_rate, subs->channels);
		ret = -EINVAL;
		goto stop_pipeline;
	}

	ret = snd_usb_lock_shutdown(subs->stream->chip);
	if (ret < 0)
		goto stop_pipeline;

	ret = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D0);
	if (ret < 0)
		goto unlock;

	ret = set_format(subs, fmt);
	if (ret < 0)
		goto unlock;

	subs->interface = fmt->iface;
	subs->altset_idx = fmt->altset_idx;
	subs->need_setup_ep = true;

 unlock:
	snd_usb_unlock_shutdown(subs->stream->chip);
	if (ret < 0)
		goto stop_pipeline;
	return ret;

 stop_pipeline:
	snd_media_stop_pipeline(subs);
	return ret;
}