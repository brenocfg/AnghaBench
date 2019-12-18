#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct snd_usb_substream {int need_setup_ep; scalar_t__ direction; TYPE_1__* stream; scalar_t__ last_frame_number; scalar_t__ last_delay; scalar_t__ transfer_done; scalar_t__ hwptr_done; TYPE_4__* data_endpoint; int /*<<< orphan*/  cur_rate; TYPE_3__* cur_audiofmt; TYPE_2__* dev; TYPE_4__* sync_endpoint; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ delay; struct snd_usb_substream* private_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  curpacksize; void* curframesize; int /*<<< orphan*/  maxpacksize; void* maxframesize; } ;
struct TYPE_8__ {size_t altset_idx; int /*<<< orphan*/  iface; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  UAC3_PD_STATE_D0 ; 
 void* bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int configure_endpoint (struct snd_usb_substream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int set_format (struct snd_usb_substream*,TYPE_3__*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_usb_endpoint_sync_pending_stop (TYPE_4__*) ; 
 int snd_usb_init_sample_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_host_interface*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int snd_usb_lock_shutdown (int /*<<< orphan*/ ) ; 
 int snd_usb_pcm_change_state (struct snd_usb_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (int /*<<< orphan*/ ) ; 
 int start_endpoints (struct snd_usb_substream*) ; 
 struct usb_interface* usb_ifnum_to_if (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_usb_substream *subs = runtime->private_data;
	struct usb_host_interface *alts;
	struct usb_interface *iface;
	int ret;

	if (! subs->cur_audiofmt) {
		dev_err(&subs->dev->dev, "no format is specified!\n");
		return -ENXIO;
	}

	ret = snd_usb_lock_shutdown(subs->stream->chip);
	if (ret < 0)
		return ret;
	if (snd_BUG_ON(!subs->data_endpoint)) {
		ret = -EIO;
		goto unlock;
	}

	snd_usb_endpoint_sync_pending_stop(subs->sync_endpoint);
	snd_usb_endpoint_sync_pending_stop(subs->data_endpoint);

	ret = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D0);
	if (ret < 0)
		goto unlock;

	ret = set_format(subs, subs->cur_audiofmt);
	if (ret < 0)
		goto unlock;

	if (subs->need_setup_ep) {

		iface = usb_ifnum_to_if(subs->dev, subs->cur_audiofmt->iface);
		alts = &iface->altsetting[subs->cur_audiofmt->altset_idx];
		ret = snd_usb_init_sample_rate(subs->stream->chip,
					       subs->cur_audiofmt->iface,
					       alts,
					       subs->cur_audiofmt,
					       subs->cur_rate);
		if (ret < 0)
			goto unlock;

		ret = configure_endpoint(subs);
		if (ret < 0)
			goto unlock;
		subs->need_setup_ep = false;
	}

	/* some unit conversions in runtime */
	subs->data_endpoint->maxframesize =
		bytes_to_frames(runtime, subs->data_endpoint->maxpacksize);
	subs->data_endpoint->curframesize =
		bytes_to_frames(runtime, subs->data_endpoint->curpacksize);

	/* reset the pointer */
	subs->hwptr_done = 0;
	subs->transfer_done = 0;
	subs->last_delay = 0;
	subs->last_frame_number = 0;
	runtime->delay = 0;

	/* for playback, submit the URBs now; otherwise, the first hwptr_done
	 * updates for all URBs would happen at the same time when starting */
	if (subs->direction == SNDRV_PCM_STREAM_PLAYBACK)
		ret = start_endpoints(subs);

 unlock:
	snd_usb_unlock_shutdown(subs->stream->chip);
	return ret;
}