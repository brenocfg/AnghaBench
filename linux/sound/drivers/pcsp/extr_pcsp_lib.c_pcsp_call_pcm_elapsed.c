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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {struct snd_pcm_substream* playback_substream; int /*<<< orphan*/  timer_active; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__ pcsp_chip ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static void pcsp_call_pcm_elapsed(unsigned long priv)
{
	if (atomic_read(&pcsp_chip.timer_active)) {
		struct snd_pcm_substream *substream;
		substream = pcsp_chip.playback_substream;
		if (substream)
			snd_pcm_period_elapsed(substream);
	}
}