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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct pcm_substream {int dummy; } ;
struct pcm_runtime {struct pcm_substream playback; TYPE_2__* chip; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static struct pcm_substream *hiface_pcm_get_substream(struct snd_pcm_substream
						      *alsa_sub)
{
	struct pcm_runtime *rt = snd_pcm_substream_chip(alsa_sub);
	struct device *device = &rt->chip->dev->dev;

	if (alsa_sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return &rt->playback;

	dev_err(device, "Error getting pcm substream slot.\n");
	return NULL;
}