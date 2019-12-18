#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ time; int /*<<< orphan*/  code; } ;
union evrec {TYPE_3__ t; } ;
struct TYPE_4__ {scalar_t__ tick; } ;
struct snd_seq_event {int /*<<< orphan*/  data; TYPE_1__ time; int /*<<< orphan*/  type; scalar_t__ flags; } ;
struct seq_oss_writeq {scalar_t__ sync_time; int sync_event_put; int /*<<< orphan*/  sync_sleep; struct seq_oss_devinfo* dp; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; TYPE_2__ addr; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  ev ;
typedef  scalar_t__ abstime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  SEQ_SYNCTIMER ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_ECHO ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_kernel_client_enqueue (int /*<<< orphan*/ ,struct snd_seq_event*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_seq_oss_fill_addr (struct seq_oss_devinfo*,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_seq_oss_timer_cur_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
snd_seq_oss_writeq_sync(struct seq_oss_writeq *q)
{
	struct seq_oss_devinfo *dp = q->dp;
	abstime_t time;

	time = snd_seq_oss_timer_cur_tick(dp->timer);
	if (q->sync_time >= time)
		return 0; /* already finished */

	if (! q->sync_event_put) {
		struct snd_seq_event ev;
		union evrec *rec;

		/* put echoback event */
		memset(&ev, 0, sizeof(ev));
		ev.flags = 0;
		ev.type = SNDRV_SEQ_EVENT_ECHO;
		ev.time.tick = time;
		/* echo back to itself */
		snd_seq_oss_fill_addr(dp, &ev, dp->addr.client, dp->addr.port);
		rec = (union evrec *)&ev.data;
		rec->t.code = SEQ_SYNCTIMER;
		rec->t.time = time;
		q->sync_event_put = 1;
		snd_seq_kernel_client_enqueue(dp->cseq, &ev, NULL, true);
	}

	wait_event_interruptible_timeout(q->sync_sleep, ! q->sync_event_put, HZ);
	if (signal_pending(current))
		/* interrupted - return 0 to finish sync */
		q->sync_event_put = 0;
	if (! q->sync_event_put || q->sync_time >= time)
		return 0;
	return 1;
}