#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_substream {int interface; TYPE_2__* stream; int /*<<< orphan*/ * pcm_substream; int /*<<< orphan*/  dev; } ;
struct snd_usb_stream {TYPE_1__* chip; struct snd_usb_substream* substream; } ;
struct snd_pcm_substream {int stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip; } ;
struct TYPE_3__ {int /*<<< orphan*/  keep_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC3_PD_STATE_D1 ; 
 int /*<<< orphan*/  snd_media_stop_pipeline (struct snd_usb_substream*) ; 
 struct snd_usb_stream* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_usb_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_lock_shutdown (int /*<<< orphan*/ ) ; 
 int snd_usb_pcm_change_state (struct snd_usb_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_endpoints (struct snd_usb_substream*,int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_pcm_close(struct snd_pcm_substream *substream)
{
	int direction = substream->stream;
	struct snd_usb_stream *as = snd_pcm_substream_chip(substream);
	struct snd_usb_substream *subs = &as->substream[direction];
	int ret;

	stop_endpoints(subs, true);
	snd_media_stop_pipeline(subs);

	if (!as->chip->keep_iface &&
	    subs->interface >= 0 &&
	    !snd_usb_lock_shutdown(subs->stream->chip)) {
		usb_set_interface(subs->dev, subs->interface, 0);
		subs->interface = -1;
		ret = snd_usb_pcm_change_state(subs, UAC3_PD_STATE_D1);
		snd_usb_unlock_shutdown(subs->stream->chip);
		if (ret < 0)
			return ret;
	}

	subs->pcm_substream = NULL;
	snd_usb_autosuspend(subs->stream->chip);

	return 0;
}