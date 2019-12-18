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
struct snd_line6_pcm {TYPE_1__* line6; } ;
struct TYPE_2__ {int iso_buffers; } ;

/* Variables and functions */
 int submit_audio_in_urb (struct snd_line6_pcm*) ; 

int line6_submit_audio_in_all_urbs(struct snd_line6_pcm *line6pcm)
{
	int ret = 0, i;

	for (i = 0; i < line6pcm->line6->iso_buffers; ++i) {
		ret = submit_audio_in_urb(line6pcm);
		if (ret < 0)
			break;
	}

	return ret;
}