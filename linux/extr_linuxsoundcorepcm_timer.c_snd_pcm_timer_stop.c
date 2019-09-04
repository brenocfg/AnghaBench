#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_timer {int dummy; } ;
struct snd_pcm_substream {scalar_t__ timer_running; } ;

/* Variables and functions */
 struct snd_pcm_substream* snd_timer_chip (struct snd_timer*) ; 

__attribute__((used)) static int snd_pcm_timer_stop(struct snd_timer * timer)
{
	struct snd_pcm_substream *substream;

	substream = snd_timer_chip(timer);
	substream->timer_running = 0;
	return 0;
}