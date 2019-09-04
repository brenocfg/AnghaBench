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
struct seq_oss_readq {scalar_t__ qlen; scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  pre_event_timeout; int /*<<< orphan*/  midi_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
snd_seq_oss_readq_wait(struct seq_oss_readq *q)
{
	wait_event_interruptible_timeout(q->midi_sleep,
					 (q->qlen > 0 || q->head == q->tail),
					 q->pre_event_timeout);
}