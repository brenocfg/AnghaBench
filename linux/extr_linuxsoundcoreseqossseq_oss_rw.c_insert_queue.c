#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union evrec {int dummy; } evrec ;
struct TYPE_6__ {int /*<<< orphan*/  tick; } ;
struct snd_seq_event {TYPE_2__ time; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  client; int /*<<< orphan*/  port; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; int /*<<< orphan*/  file_mode; TYPE_3__* timer; TYPE_1__ addr; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_7__ {int /*<<< orphan*/  running; scalar_t__ realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_NOTEOFF ; 
 scalar_t__ is_nonblock_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 int snd_seq_kernel_client_enqueue (int /*<<< orphan*/ ,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_seq_kernel_client_enqueue_blocking (int /*<<< orphan*/ ,struct snd_seq_event*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_oss_dispatch (struct seq_oss_devinfo*,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_oss_fill_addr (struct seq_oss_devinfo*,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_seq_oss_process_event (struct seq_oss_devinfo*,union evrec*,struct snd_seq_event*) ; 
 scalar_t__ snd_seq_oss_process_timer_event (TYPE_3__*,union evrec*) ; 
 int /*<<< orphan*/  snd_seq_oss_timer_cur_tick (TYPE_3__*) ; 

__attribute__((used)) static int
insert_queue(struct seq_oss_devinfo *dp, union evrec *rec, struct file *opt)
{
	int rc = 0;
	struct snd_seq_event event;

	/* if this is a timing event, process the current time */
	if (snd_seq_oss_process_timer_event(dp->timer, rec))
		return 0; /* no need to insert queue */

	/* parse this event */
	memset(&event, 0, sizeof(event));
	/* set dummy -- to be sure */
	event.type = SNDRV_SEQ_EVENT_NOTEOFF;
	snd_seq_oss_fill_addr(dp, &event, dp->addr.port, dp->addr.client);

	if (snd_seq_oss_process_event(dp, rec, &event))
		return 0; /* invalid event - no need to insert queue */

	event.time.tick = snd_seq_oss_timer_cur_tick(dp->timer);
	if (dp->timer->realtime || !dp->timer->running) {
		snd_seq_oss_dispatch(dp, &event, 0, 0);
	} else {
		if (is_nonblock_mode(dp->file_mode))
			rc = snd_seq_kernel_client_enqueue(dp->cseq, &event, 0, 0);
		else
			rc = snd_seq_kernel_client_enqueue_blocking(dp->cseq, &event, opt, 0, 0);
	}
	return rc;
}