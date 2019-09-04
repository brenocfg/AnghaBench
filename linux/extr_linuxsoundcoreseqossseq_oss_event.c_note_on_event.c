#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_event {int dummy; } ;
struct TYPE_3__ {int event_passing; } ;
struct seq_oss_synthinfo {int nr_voices; TYPE_2__* ch; TYPE_1__ arg; } ;
struct seq_oss_devinfo {int dummy; } ;
struct TYPE_4__ {int note; int vel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int SNDRV_SEQ_EVENT_KEYPRESS ; 
 int SNDRV_SEQ_EVENT_NOTEOFF ; 
 int SNDRV_SEQ_EVENT_NOTEON ; 
#define  SNDRV_SEQ_OSS_PASS_EVENTS 130 
#define  SNDRV_SEQ_OSS_PROCESS_EVENTS 129 
#define  SNDRV_SEQ_OSS_PROCESS_KEYPRESS 128 
 int array_index_nospec (int,int) ; 
 int set_note_event (struct seq_oss_devinfo*,int,int,int,int,int,struct snd_seq_event*) ; 
 struct seq_oss_synthinfo* snd_seq_oss_synth_info (struct seq_oss_devinfo*,int) ; 

__attribute__((used)) static int
note_on_event(struct seq_oss_devinfo *dp, int dev, int ch, int note, int vel, struct snd_seq_event *ev)
{
	struct seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	if (!info)
		return -ENXIO;

	switch (info->arg.event_passing) {
	case SNDRV_SEQ_OSS_PROCESS_EVENTS:
		if (! info->ch || ch < 0 || ch >= info->nr_voices) {
			/* pass directly */
			return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
		}

		ch = array_index_nospec(ch, info->nr_voices);
		if (note == 255 && info->ch[ch].note >= 0) {
			/* volume control */
			int type;
			//if (! vel)
				/* set volume to zero -- note off */
			//	type = SNDRV_SEQ_EVENT_NOTEOFF;
			//else
				if (info->ch[ch].vel)
				/* sample already started -- volume change */
				type = SNDRV_SEQ_EVENT_KEYPRESS;
			else
				/* sample not started -- start now */
				type = SNDRV_SEQ_EVENT_NOTEON;
			info->ch[ch].vel = vel;
			return set_note_event(dp, dev, type, ch, info->ch[ch].note, vel, ev);
		} else if (note >= 128)
			return -EINVAL; /* invalid */

		if (note != info->ch[ch].note && info->ch[ch].note >= 0)
			/* note changed - note off at beginning */
			set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEOFF, ch, info->ch[ch].note, 0, ev);
		/* set current status */
		info->ch[ch].note = note;
		info->ch[ch].vel = vel;
		if (vel) /* non-zero velocity - start the note now */
			return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
		return -EINVAL;
		
	case SNDRV_SEQ_OSS_PASS_EVENTS:
		/* pass the event anyway */
		return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);

	case SNDRV_SEQ_OSS_PROCESS_KEYPRESS:
		if (note >= 128) /* key pressure: shifted by 128 */
			return set_note_event(dp, dev, SNDRV_SEQ_EVENT_KEYPRESS, ch, note - 128, vel, ev);
		else /* normal note-on event */
			return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
	}
	return -EINVAL;
}