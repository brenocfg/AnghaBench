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
struct snd_usb_substream {int running; TYPE_1__* data_endpoint; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_4__ {struct snd_usb_substream* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * retire_data_urb; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 131 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 void* retire_capture_urb ; 
 int start_endpoints (struct snd_usb_substream*) ; 
 int /*<<< orphan*/  stop_endpoints (struct snd_usb_substream*,int) ; 

__attribute__((used)) static int snd_usb_substream_capture_trigger(struct snd_pcm_substream *substream,
					     int cmd)
{
	int err;
	struct snd_usb_substream *subs = substream->runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		err = start_endpoints(subs);
		if (err < 0)
			return err;

		subs->data_endpoint->retire_data_urb = retire_capture_urb;
		subs->running = 1;
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
		stop_endpoints(subs, false);
		subs->running = 0;
		return 0;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		subs->data_endpoint->retire_data_urb = NULL;
		subs->running = 0;
		return 0;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		subs->data_endpoint->retire_data_urb = retire_capture_urb;
		subs->running = 1;
		return 0;
	}

	return -EINVAL;
}