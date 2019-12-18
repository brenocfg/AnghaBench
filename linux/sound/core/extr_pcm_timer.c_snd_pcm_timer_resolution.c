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
struct snd_timer {struct snd_pcm_substream* private_data; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {unsigned long timer_resolution; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long snd_pcm_timer_resolution(struct snd_timer * timer)
{
	struct snd_pcm_substream *substream;

	substream = timer->private_data;
	return substream->runtime ? substream->runtime->timer_resolution : 0;
}