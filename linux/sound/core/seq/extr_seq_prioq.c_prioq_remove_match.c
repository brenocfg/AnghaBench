#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  time; int /*<<< orphan*/  tick; } ;
struct TYPE_8__ {scalar_t__ client; scalar_t__ port; } ;
struct snd_seq_remove_events {int remove_mode; scalar_t__ channel; int type; scalar_t__ tag; TYPE_6__ time; TYPE_2__ dest; } ;
struct TYPE_11__ {int /*<<< orphan*/  time; int /*<<< orphan*/  tick; } ;
struct TYPE_9__ {scalar_t__ channel; } ;
struct TYPE_10__ {TYPE_3__ note; } ;
struct TYPE_7__ {scalar_t__ client; scalar_t__ port; } ;
struct snd_seq_event {int type; scalar_t__ tag; TYPE_5__ time; TYPE_4__ data; TYPE_1__ dest; } ;

/* Variables and functions */
#define  SNDRV_SEQ_EVENT_NOTEOFF 128 
 int SNDRV_SEQ_REMOVE_DEST ; 
 int SNDRV_SEQ_REMOVE_DEST_CHANNEL ; 
 int SNDRV_SEQ_REMOVE_EVENT_TYPE ; 
 int SNDRV_SEQ_REMOVE_IGNORE_OFF ; 
 int SNDRV_SEQ_REMOVE_TAG_MATCH ; 
 int SNDRV_SEQ_REMOVE_TIME_AFTER ; 
 int SNDRV_SEQ_REMOVE_TIME_BEFORE ; 
 int SNDRV_SEQ_REMOVE_TIME_TICK ; 
 int snd_seq_compare_real_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_seq_compare_tick_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_ev_is_channel_type (struct snd_seq_event*) ; 

__attribute__((used)) static int prioq_remove_match(struct snd_seq_remove_events *info,
			      struct snd_seq_event *ev)
{
	int res;

	if (info->remove_mode & SNDRV_SEQ_REMOVE_DEST) {
		if (ev->dest.client != info->dest.client ||
				ev->dest.port != info->dest.port)
			return 0;
	}
	if (info->remove_mode & SNDRV_SEQ_REMOVE_DEST_CHANNEL) {
		if (! snd_seq_ev_is_channel_type(ev))
			return 0;
		/* data.note.channel and data.control.channel are identical */
		if (ev->data.note.channel != info->channel)
			return 0;
	}
	if (info->remove_mode & SNDRV_SEQ_REMOVE_TIME_AFTER) {
		if (info->remove_mode & SNDRV_SEQ_REMOVE_TIME_TICK)
			res = snd_seq_compare_tick_time(&ev->time.tick, &info->time.tick);
		else
			res = snd_seq_compare_real_time(&ev->time.time, &info->time.time);
		if (!res)
			return 0;
	}
	if (info->remove_mode & SNDRV_SEQ_REMOVE_TIME_BEFORE) {
		if (info->remove_mode & SNDRV_SEQ_REMOVE_TIME_TICK)
			res = snd_seq_compare_tick_time(&ev->time.tick, &info->time.tick);
		else
			res = snd_seq_compare_real_time(&ev->time.time, &info->time.time);
		if (res)
			return 0;
	}
	if (info->remove_mode & SNDRV_SEQ_REMOVE_EVENT_TYPE) {
		if (ev->type != info->type)
			return 0;
	}
	if (info->remove_mode & SNDRV_SEQ_REMOVE_IGNORE_OFF) {
		/* Do not remove off events */
		switch (ev->type) {
		case SNDRV_SEQ_EVENT_NOTEOFF:
		/* case SNDRV_SEQ_EVENT_SAMPLE_STOP: */
			return 0;
		default:
			break;
		}
	}
	if (info->remove_mode & SNDRV_SEQ_REMOVE_TAG_MATCH) {
		if (info->tag != ev->tag)
			return 0;
	}

	return 1;
}