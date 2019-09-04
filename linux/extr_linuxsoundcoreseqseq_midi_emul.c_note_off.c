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
struct snd_midi_op {int /*<<< orphan*/  (* note_off ) (void*,int,int,struct snd_midi_channel*) ;} ;
struct snd_midi_channel {int* note; scalar_t__ gm_hold; } ;

/* Variables and functions */
 int SNDRV_MIDI_NOTE_RELEASED ; 
 int SNDRV_MIDI_NOTE_SOSTENUTO ; 
 int /*<<< orphan*/  stub1 (void*,int,int,struct snd_midi_channel*) ; 

__attribute__((used)) static void
note_off(struct snd_midi_op *ops, void *drv, struct snd_midi_channel *chan,
	 int note, int vel)
{
	if (chan->gm_hold) {
		/* Hold this note until pedal is turned off */
		chan->note[note] |= SNDRV_MIDI_NOTE_RELEASED;
	} else if (chan->note[note] & SNDRV_MIDI_NOTE_SOSTENUTO) {
		/* Mark this note as release; it will be turned off when sostenuto
		 * is turned off */
		chan->note[note] |= SNDRV_MIDI_NOTE_RELEASED;
	} else {
		chan->note[note] = 0;
		if (ops->note_off)
			ops->note_off(drv, note, vel, chan);
	}
}