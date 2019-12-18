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
struct snd_midi_event {int nostat; } ;

/* Variables and functions */

void snd_midi_event_no_status(struct snd_midi_event *dev, int on)
{
	dev->nostat = on ? 1 : 0;
}