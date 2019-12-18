#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_riptide {int /*<<< orphan*/ ** playback_substream; } ;
struct snd_pcm_substream {int number; TYPE_1__* runtime; } ;
struct pcmhw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 struct pcmhw* get_pcmhwdev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  kfree (struct pcmhw*) ; 
 struct snd_riptide* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_riptide_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_riptide *chip = snd_pcm_substream_chip(substream);
	struct pcmhw *data = get_pcmhwdev(substream);
	int sub_num = substream->number;

	substream->runtime->private_data = NULL;
	chip->playback_substream[sub_num] = NULL;
	kfree(data);
	return 0;
}