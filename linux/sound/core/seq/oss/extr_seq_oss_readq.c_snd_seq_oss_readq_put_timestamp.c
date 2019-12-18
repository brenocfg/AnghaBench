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
struct TYPE_2__ {unsigned long time; int /*<<< orphan*/  cmd; int /*<<< orphan*/  code; } ;
union evrec {unsigned long echo; TYPE_1__ t; } ;
struct seq_oss_readq {unsigned long input_time; } ;
typedef  int /*<<< orphan*/  rec ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMING ; 
 unsigned long SEQ_WAIT ; 
#define  SNDRV_SEQ_OSS_MODE_MUSIC 129 
#define  SNDRV_SEQ_OSS_MODE_SYNTH 128 
 int /*<<< orphan*/  TMR_WAIT_ABS ; 
 int /*<<< orphan*/  memset (union evrec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_put_event (struct seq_oss_readq*,union evrec*) ; 

int
snd_seq_oss_readq_put_timestamp(struct seq_oss_readq *q, unsigned long curt, int seq_mode)
{
	if (curt != q->input_time) {
		union evrec rec;
		memset(&rec, 0, sizeof(rec));
		switch (seq_mode) {
		case SNDRV_SEQ_OSS_MODE_SYNTH:
			rec.echo = (curt << 8) | SEQ_WAIT;
			snd_seq_oss_readq_put_event(q, &rec);
			break;
		case SNDRV_SEQ_OSS_MODE_MUSIC:
			rec.t.code = EV_TIMING;
			rec.t.cmd = TMR_WAIT_ABS;
			rec.t.time = curt;
			snd_seq_oss_readq_put_event(q, &rec);
			break;
		}
		q->input_time = curt;
	}
	return 0;
}