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
struct snd_card {struct portman* private_data; } ;
struct portman {int* mode; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * midi_input; } ;

/* Variables and functions */
 int INT_REQ ; 
 int PORTMAN2X4_MODE_INPUT_TRIGGERED ; 
 scalar_t__ portman_data_avail (struct portman*,int) ; 
 unsigned char portman_read_midi (struct portman*,int) ; 
 int portman_read_status (struct portman*) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_portman_interrupt(void *userdata)
{
	unsigned char midivalue = 0;
	struct portman *pm = ((struct snd_card*)userdata)->private_data;

	spin_lock(&pm->reg_lock);

	/* While any input data is waiting */
	while ((portman_read_status(pm) & INT_REQ) == INT_REQ) {
		/* If data available on channel 0, 
		   read it and stuff it into the queue. */
		if (portman_data_avail(pm, 0)) {
			/* Read Midi */
			midivalue = portman_read_midi(pm, 0);
			/* put midi into queue... */
			if (pm->mode[0] & PORTMAN2X4_MODE_INPUT_TRIGGERED)
				snd_rawmidi_receive(pm->midi_input[0],
						    &midivalue, 1);

		}
		/* If data available on channel 1, 
		   read it and stuff it into the queue. */
		if (portman_data_avail(pm, 1)) {
			/* Read Midi */
			midivalue = portman_read_midi(pm, 1);
			/* put midi into queue... */
			if (pm->mode[1] & PORTMAN2X4_MODE_INPUT_TRIGGERED)
				snd_rawmidi_receive(pm->midi_input[1],
						    &midivalue, 1);
		}

	}

	spin_unlock(&pm->reg_lock);
}