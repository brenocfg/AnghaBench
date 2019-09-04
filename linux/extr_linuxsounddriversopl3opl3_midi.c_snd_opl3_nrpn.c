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
struct snd_midi_channel_set {int dummy; } ;
struct snd_midi_channel {int dummy; } ;

/* Variables and functions */

void snd_opl3_nrpn(void *p, struct snd_midi_channel *chan,
		   struct snd_midi_channel_set *chset)
{
#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "NRPN, ch#: %i, inst#: %i\n",
		   chan->number, chan->midi_program);
#endif
}