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
struct TYPE_2__ {int chn; int cmd; int /*<<< orphan*/  parm; int /*<<< orphan*/  note; int /*<<< orphan*/  dev; } ;
union evrec {TYPE_1__ v; } ;
struct snd_seq_event {int dummy; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MIDI_KEY_PRESSURE 130 
#define  MIDI_NOTEOFF 129 
#define  MIDI_NOTEON 128 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_KEYPRESS ; 
 int note_off_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_event*) ; 
 int note_on_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_event*) ; 
 int set_note_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_event*) ; 

__attribute__((used)) static int
chn_voice_event(struct seq_oss_devinfo *dp, union evrec *q, struct snd_seq_event *ev)
{
	if (q->v.chn >= 32)
		return -EINVAL;
	switch (q->v.cmd) {
	case MIDI_NOTEON:
		return note_on_event(dp, q->v.dev, q->v.chn, q->v.note, q->v.parm, ev);

	case MIDI_NOTEOFF:
		return note_off_event(dp, q->v.dev, q->v.chn, q->v.note, q->v.parm, ev);

	case MIDI_KEY_PRESSURE:
		return set_note_event(dp, q->v.dev, SNDRV_SEQ_EVENT_KEYPRESS,
				       q->v.chn, q->v.note, q->v.parm, ev);

	}
	return -EINVAL;
}