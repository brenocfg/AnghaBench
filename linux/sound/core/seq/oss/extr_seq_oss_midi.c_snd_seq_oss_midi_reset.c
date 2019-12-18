#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int channel; scalar_t__ value; int /*<<< orphan*/  param; } ;
struct TYPE_8__ {TYPE_3__ control; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_event {TYPE_4__ data; int /*<<< orphan*/  type; TYPE_2__ source; int /*<<< orphan*/  queue; TYPE_1__ dest; } ;
struct seq_oss_midi {int opened; int /*<<< orphan*/  use_lock; int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_devinfo {scalar_t__ seq_mode; int /*<<< orphan*/  port; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  MIDI_CTL_ALL_NOTES_OFF ; 
 int /*<<< orphan*/  MIDI_CTL_RESET_CONTROLLERS ; 
 int PERM_WRITE ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTROLLER ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_PITCHBEND ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_SENSING ; 
 scalar_t__ SNDRV_SEQ_OSS_MODE_MUSIC ; 
 scalar_t__ SNDRV_SEQ_OSS_MODE_SYNTH ; 
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_oss_dispatch (struct seq_oss_devinfo*,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 

void
snd_seq_oss_midi_reset(struct seq_oss_devinfo *dp, int dev)
{
	struct seq_oss_midi *mdev;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return;
	if (! mdev->opened) {
		snd_use_lock_free(&mdev->use_lock);
		return;
	}

	if (mdev->opened & PERM_WRITE) {
		struct snd_seq_event ev;
		int c;

		memset(&ev, 0, sizeof(ev));
		ev.dest.client = mdev->client;
		ev.dest.port = mdev->port;
		ev.queue = dp->queue;
		ev.source.port = dp->port;
		if (dp->seq_mode == SNDRV_SEQ_OSS_MODE_SYNTH) {
			ev.type = SNDRV_SEQ_EVENT_SENSING;
			snd_seq_oss_dispatch(dp, &ev, 0, 0);
		}
		for (c = 0; c < 16; c++) {
			ev.type = SNDRV_SEQ_EVENT_CONTROLLER;
			ev.data.control.channel = c;
			ev.data.control.param = MIDI_CTL_ALL_NOTES_OFF;
			snd_seq_oss_dispatch(dp, &ev, 0, 0);
			if (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC) {
				ev.data.control.param =
					MIDI_CTL_RESET_CONTROLLERS;
				snd_seq_oss_dispatch(dp, &ev, 0, 0);
				ev.type = SNDRV_SEQ_EVENT_PITCHBEND;
				ev.data.control.value = 0;
				snd_seq_oss_dispatch(dp, &ev, 0, 0);
			}
		}
	}
	// snd_seq_oss_midi_close(dp, dev);
	snd_use_lock_free(&mdev->use_lock);
}