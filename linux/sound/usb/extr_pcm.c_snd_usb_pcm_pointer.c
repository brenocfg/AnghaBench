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
struct snd_usb_substream {unsigned int hwptr_done; int /*<<< orphan*/  lock; TYPE_3__* stream; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
typedef  unsigned int snd_pcm_uframes_t ;
struct TYPE_6__ {TYPE_2__* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  shutdown; } ;
struct TYPE_4__ {int frame_bits; int /*<<< orphan*/  rate; int /*<<< orphan*/  delay; struct snd_usb_substream* private_data; } ;

/* Variables and functions */
 unsigned int SNDRV_PCM_POS_XRUN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usb_pcm_delay (struct snd_usb_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_usb_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_usb_substream *subs = substream->runtime->private_data;
	unsigned int hwptr_done;

	if (atomic_read(&subs->stream->chip->shutdown))
		return SNDRV_PCM_POS_XRUN;
	spin_lock(&subs->lock);
	hwptr_done = subs->hwptr_done;
	substream->runtime->delay = snd_usb_pcm_delay(subs,
						substream->runtime->rate);
	spin_unlock(&subs->lock);
	return hwptr_done / (substream->runtime->frame_bits >> 3);
}