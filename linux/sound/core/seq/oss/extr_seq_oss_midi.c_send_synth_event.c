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
struct TYPE_9__ {int /*<<< orphan*/  chn; int /*<<< orphan*/  val; void* code; int /*<<< orphan*/  p1; int /*<<< orphan*/  cmd; } ;
struct TYPE_7__ {int dev; int /*<<< orphan*/  chn; int /*<<< orphan*/  parm; int /*<<< orphan*/  note; int /*<<< orphan*/  code; int /*<<< orphan*/  cmd; } ;
union evrec {TYPE_3__ l; TYPE_1__ v; } ;
struct TYPE_12__ {int /*<<< orphan*/  tick; } ;
struct TYPE_10__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  value; int /*<<< orphan*/  param; } ;
struct TYPE_8__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  velocity; int /*<<< orphan*/  note; } ;
struct TYPE_11__ {TYPE_4__ control; TYPE_2__ note; } ;
struct snd_seq_event {int type; TYPE_6__ time; TYPE_5__ data; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  readq; int /*<<< orphan*/  seq_mode; } ;
typedef  int /*<<< orphan*/  ossev ;

/* Variables and functions */
 void* EV_CHN_COMMON ; 
 int /*<<< orphan*/  EV_CHN_VOICE ; 
 int /*<<< orphan*/  MIDI_CHN_PRESSURE ; 
 int /*<<< orphan*/  MIDI_CTL_CHANGE ; 
 int /*<<< orphan*/  MIDI_KEY_PRESSURE ; 
 int /*<<< orphan*/  MIDI_NOTEOFF ; 
 int /*<<< orphan*/  MIDI_NOTEON ; 
 int /*<<< orphan*/  MIDI_PGM_CHANGE ; 
 int /*<<< orphan*/  MIDI_PITCH_BEND ; 
#define  SNDRV_SEQ_EVENT_CHANPRESS 134 
#define  SNDRV_SEQ_EVENT_CONTROLLER 133 
#define  SNDRV_SEQ_EVENT_KEYPRESS 132 
#define  SNDRV_SEQ_EVENT_NOTEOFF 131 
#define  SNDRV_SEQ_EVENT_NOTEON 130 
#define  SNDRV_SEQ_EVENT_PGMCHANGE 129 
#define  SNDRV_SEQ_EVENT_PITCHBEND 128 
 int /*<<< orphan*/  memset (union evrec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_put_event (int /*<<< orphan*/ ,union evrec*) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_put_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_synth_event(struct seq_oss_devinfo *dp, struct snd_seq_event *ev, int dev)
{
	union evrec ossev;

	memset(&ossev, 0, sizeof(ossev));

	switch (ev->type) {
	case SNDRV_SEQ_EVENT_NOTEON:
		ossev.v.cmd = MIDI_NOTEON; break;
	case SNDRV_SEQ_EVENT_NOTEOFF:
		ossev.v.cmd = MIDI_NOTEOFF; break;
	case SNDRV_SEQ_EVENT_KEYPRESS:
		ossev.v.cmd = MIDI_KEY_PRESSURE; break;
	case SNDRV_SEQ_EVENT_CONTROLLER:
		ossev.l.cmd = MIDI_CTL_CHANGE; break;
	case SNDRV_SEQ_EVENT_PGMCHANGE:
		ossev.l.cmd = MIDI_PGM_CHANGE; break;
	case SNDRV_SEQ_EVENT_CHANPRESS:
		ossev.l.cmd = MIDI_CHN_PRESSURE; break;
	case SNDRV_SEQ_EVENT_PITCHBEND:
		ossev.l.cmd = MIDI_PITCH_BEND; break;
	default:
		return 0; /* not supported */
	}

	ossev.v.dev = dev;

	switch (ev->type) {
	case SNDRV_SEQ_EVENT_NOTEON:
	case SNDRV_SEQ_EVENT_NOTEOFF:
	case SNDRV_SEQ_EVENT_KEYPRESS:
		ossev.v.code = EV_CHN_VOICE;
		ossev.v.note = ev->data.note.note;
		ossev.v.parm = ev->data.note.velocity;
		ossev.v.chn = ev->data.note.channel;
		break;
	case SNDRV_SEQ_EVENT_CONTROLLER:
	case SNDRV_SEQ_EVENT_PGMCHANGE:
	case SNDRV_SEQ_EVENT_CHANPRESS:
		ossev.l.code = EV_CHN_COMMON;
		ossev.l.p1 = ev->data.control.param;
		ossev.l.val = ev->data.control.value;
		ossev.l.chn = ev->data.control.channel;
		break;
	case SNDRV_SEQ_EVENT_PITCHBEND:
		ossev.l.code = EV_CHN_COMMON;
		ossev.l.val = ev->data.control.value + 8192;
		ossev.l.chn = ev->data.control.channel;
		break;
	}
	
	snd_seq_oss_readq_put_timestamp(dp->readq, ev->time.tick, dp->seq_mode);
	snd_seq_oss_readq_put_event(dp->readq, &ossev);

	return 0;
}