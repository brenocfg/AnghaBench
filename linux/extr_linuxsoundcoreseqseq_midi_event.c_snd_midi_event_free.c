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
struct snd_midi_event {struct snd_midi_event* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_midi_event*) ; 

void snd_midi_event_free(struct snd_midi_event *dev)
{
	if (dev != NULL) {
		kfree(dev->buf);
		kfree(dev);
	}
}