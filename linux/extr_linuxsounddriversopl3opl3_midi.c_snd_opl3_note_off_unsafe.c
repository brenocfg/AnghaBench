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
struct snd_opl3_voice {scalar_t__ state; int note; struct snd_midi_channel* chan; } ;
struct snd_opl3 {scalar_t__ synth_mode; int max_voices; struct snd_opl3_voice* voices; } ;
struct snd_midi_channel {size_t number; scalar_t__ drum_channel; } ;

/* Variables and functions */
 size_t MAX_OPL3_VOICES ; 
 scalar_t__ SNDRV_OPL3_MODE_SEQ ; 
 int /*<<< orphan*/  snd_opl3_drum_switch (struct snd_opl3*,int,int,int /*<<< orphan*/ ,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  snd_opl3_kill_voice (struct snd_opl3*,int) ; 
 int* snd_opl3_oss_map ; 
 scalar_t__ use_internal_drums ; 

__attribute__((used)) static void snd_opl3_note_off_unsafe(void *p, int note, int vel,
				     struct snd_midi_channel *chan)
{
  	struct snd_opl3 *opl3;

	int voice;
	struct snd_opl3_voice *vp;

	opl3 = p;

#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "Note off, ch %i, inst %i, note %i\n",
		   chan->number, chan->midi_program, note);
#endif

	if (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) {
		if (chan->drum_channel && use_internal_drums) {
			snd_opl3_drum_switch(opl3, note, vel, 0, chan);
			return;
		}
		/* this loop will hopefully kill all extra voices, because
		   they are grouped by the same channel and note values */
		for (voice = 0; voice < opl3->max_voices; voice++) {
			vp = &opl3->voices[voice];
			if (vp->state > 0 && vp->chan == chan && vp->note == note) {
				snd_opl3_kill_voice(opl3, voice);
			}
		}
	} else {
		/* remap OSS voices */
		if (chan->number < MAX_OPL3_VOICES) {
			voice = snd_opl3_oss_map[chan->number];		
			snd_opl3_kill_voice(opl3, voice);
		}
	}
}