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
struct snd_sgio2audio_chan {size_t idx; } ;
struct snd_sgio2audio {TYPE_1__* channel; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_4__ {struct snd_sgio2audio_chan* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct snd_sgio2audio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_sgio2audio_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	struct snd_sgio2audio_chan *chan = substream->runtime->private_data;

	/* get the current hardware pointer */
	return bytes_to_frames(substream->runtime,
			       chip->channel[chan->idx].pos);
}