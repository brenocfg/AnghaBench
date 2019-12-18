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
struct TYPE_3__ {int /*<<< orphan*/  tick; } ;
struct snd_seq_event {scalar_t__ type; TYPE_1__ time; } ;
struct seq_oss_midi {int /*<<< orphan*/  seq_device; int /*<<< orphan*/  coder; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  readq; TYPE_2__* timer; int /*<<< orphan*/  seq_mode; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int /*<<< orphan*/  running; } ;

/* Variables and functions */
 scalar_t__ SNDRV_SEQ_EVENT_SYSEX ; 
 int snd_midi_event_decode (int /*<<< orphan*/ ,char*,int,struct snd_seq_event*) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_put_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_sysex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_event*) ; 
 int snd_seq_oss_timer_start (TYPE_2__*) ; 

__attribute__((used)) static int
send_midi_event(struct seq_oss_devinfo *dp, struct snd_seq_event *ev, struct seq_oss_midi *mdev)
{
	char msg[32];
	int len;
	
	snd_seq_oss_readq_put_timestamp(dp->readq, ev->time.tick, dp->seq_mode);
	if (!dp->timer->running)
		len = snd_seq_oss_timer_start(dp->timer);
	if (ev->type == SNDRV_SEQ_EVENT_SYSEX) {
		snd_seq_oss_readq_sysex(dp->readq, mdev->seq_device, ev);
	} else {
		len = snd_midi_event_decode(mdev->coder, msg, sizeof(msg), ev);
		if (len > 0)
			snd_seq_oss_readq_puts(dp->readq, mdev->seq_device, msg, len);
	}

	return 0;
}