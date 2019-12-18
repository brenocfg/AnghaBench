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
struct snd_usb_substream {TYPE_1__* stream; int /*<<< orphan*/  data_endpoint; int /*<<< orphan*/  sync_endpoint; scalar_t__ period_bytes; scalar_t__ cur_rate; int /*<<< orphan*/ * cur_audiofmt; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_4__ {struct snd_usb_substream* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_media_stop_pipeline (struct snd_usb_substream*) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_free_vmalloc_buffer (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_usb_endpoint_deactivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_lock_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_usb_use_vmalloc ; 
 int /*<<< orphan*/  stop_endpoints (struct snd_usb_substream*,int) ; 

__attribute__((used)) static int snd_usb_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_usb_substream *subs = substream->runtime->private_data;

	snd_media_stop_pipeline(subs);
	subs->cur_audiofmt = NULL;
	subs->cur_rate = 0;
	subs->period_bytes = 0;
	if (!snd_usb_lock_shutdown(subs->stream->chip)) {
		stop_endpoints(subs, true);
		snd_usb_endpoint_deactivate(subs->sync_endpoint);
		snd_usb_endpoint_deactivate(subs->data_endpoint);
		snd_usb_unlock_shutdown(subs->stream->chip);
	}

	if (snd_usb_use_vmalloc)
		return snd_pcm_lib_free_vmalloc_buffer(substream);
	else
		return snd_pcm_lib_free_pages(substream);
}