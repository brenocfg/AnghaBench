#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_seq_queue {int /*<<< orphan*/  queue; TYPE_3__* timer; } ;
struct TYPE_14__ {int /*<<< orphan*/  client; } ;
struct TYPE_13__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct TYPE_11__ {int /*<<< orphan*/  queue; } ;
struct TYPE_12__ {TYPE_4__ queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  tick; } ;
struct snd_seq_event {int flags; TYPE_7__ dest; TYPE_6__ source; TYPE_5__ data; int /*<<< orphan*/  queue; TYPE_1__ time; } ;
struct TYPE_9__ {int /*<<< orphan*/  cur_tick; } ;
struct TYPE_10__ {TYPE_2__ tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_ADDRESS_SUBSCRIBERS ; 
 int /*<<< orphan*/  SNDRV_SEQ_CLIENT_SYSTEM ; 
 int /*<<< orphan*/  SNDRV_SEQ_PORT_SYSTEM_TIMER ; 
 int SNDRV_SEQ_TIME_MODE_ABS ; 
 int SNDRV_SEQ_TIME_STAMP_TICK ; 
 int /*<<< orphan*/  snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int,int) ; 

__attribute__((used)) static void queue_broadcast_event(struct snd_seq_queue *q, struct snd_seq_event *ev,
				  int atomic, int hop)
{
	struct snd_seq_event sev;

	sev = *ev;
	
	sev.flags = SNDRV_SEQ_TIME_STAMP_TICK|SNDRV_SEQ_TIME_MODE_ABS;
	sev.time.tick = q->timer->tick.cur_tick;
	sev.queue = q->queue;
	sev.data.queue.queue = q->queue;

	/* broadcast events from Timer port */
	sev.source.client = SNDRV_SEQ_CLIENT_SYSTEM;
	sev.source.port = SNDRV_SEQ_PORT_SYSTEM_TIMER;
	sev.dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
	snd_seq_kernel_client_dispatch(SNDRV_SEQ_CLIENT_SYSTEM, &sev, atomic, hop);
}