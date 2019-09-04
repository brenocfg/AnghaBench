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
typedef  int /*<<< orphan*/  tmprec ;
struct snd_seq_queue_tempo {int /*<<< orphan*/  tempo; int /*<<< orphan*/  ppq; int /*<<< orphan*/  queue; } ;
struct seq_oss_timer {int running; scalar_t__ cur_tick; int /*<<< orphan*/  tempo; int /*<<< orphan*/  ppq; struct seq_oss_devinfo* dp; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_START ; 
 int /*<<< orphan*/  memset (struct snd_seq_queue_tempo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_timer_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_oss_timer_stop (struct seq_oss_timer*) ; 
 int /*<<< orphan*/  snd_seq_set_queue_tempo (int /*<<< orphan*/ ,struct snd_seq_queue_tempo*) ; 

int
snd_seq_oss_timer_start(struct seq_oss_timer *timer)
{
	struct seq_oss_devinfo *dp = timer->dp;
	struct snd_seq_queue_tempo tmprec;

	if (timer->running)
		snd_seq_oss_timer_stop(timer);

	memset(&tmprec, 0, sizeof(tmprec));
	tmprec.queue = dp->queue;
	tmprec.ppq = timer->ppq;
	tmprec.tempo = timer->tempo;
	snd_seq_set_queue_tempo(dp->cseq, &tmprec);

	send_timer_event(dp, SNDRV_SEQ_EVENT_START, 0);
	timer->running = 1;
	timer->cur_tick = 0;
	return 0;
}