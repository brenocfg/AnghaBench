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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_4__ {int dq_count; int dq_tstamp; int avg_dq_rate; int burst_time; } ;
struct pie_sched_data {TYPE_2__ vars; } ;
struct TYPE_3__ {int backlog; } ;
struct Qdisc {TYPE_1__ qstats; } ;
typedef  int psched_time_t ;

/* Variables and functions */
 int DQCOUNT_INVALID ; 
 int PIE_SCALE ; 
 int QUEUE_THRESHOLD ; 
 void* psched_get_time () ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void pie_process_dequeue(struct Qdisc *sch, struct sk_buff *skb)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	int qlen = sch->qstats.backlog;	/* current queue size in bytes */

	/* If current queue is about 10 packets or more and dq_count is unset
	 * we have enough packets to calculate the drain rate. Save
	 * current time as dq_tstamp and start measurement cycle.
	 */
	if (qlen >= QUEUE_THRESHOLD && q->vars.dq_count == DQCOUNT_INVALID) {
		q->vars.dq_tstamp = psched_get_time();
		q->vars.dq_count = 0;
	}

	/* Calculate the average drain rate from this value.  If queue length
	 * has receded to a small value viz., <= QUEUE_THRESHOLD bytes,reset
	 * the dq_count to -1 as we don't have enough packets to calculate the
	 * drain rate anymore The following if block is entered only when we
	 * have a substantial queue built up (QUEUE_THRESHOLD bytes or more)
	 * and we calculate the drain rate for the threshold here.  dq_count is
	 * in bytes, time difference in psched_time, hence rate is in
	 * bytes/psched_time.
	 */
	if (q->vars.dq_count != DQCOUNT_INVALID) {
		q->vars.dq_count += skb->len;

		if (q->vars.dq_count >= QUEUE_THRESHOLD) {
			psched_time_t now = psched_get_time();
			u32 dtime = now - q->vars.dq_tstamp;
			u32 count = q->vars.dq_count << PIE_SCALE;

			if (dtime == 0)
				return;

			count = count / dtime;

			if (q->vars.avg_dq_rate == 0)
				q->vars.avg_dq_rate = count;
			else
				q->vars.avg_dq_rate =
				    (q->vars.avg_dq_rate -
				     (q->vars.avg_dq_rate >> 3)) + (count >> 3);

			/* If the queue has receded below the threshold, we hold
			 * on to the last drain rate calculated, else we reset
			 * dq_count to 0 to re-enter the if block when the next
			 * packet is dequeued
			 */
			if (qlen < QUEUE_THRESHOLD) {
				q->vars.dq_count = DQCOUNT_INVALID;
			} else {
				q->vars.dq_count = 0;
				q->vars.dq_tstamp = psched_get_time();
			}

			if (q->vars.burst_time > 0) {
				if (q->vars.burst_time > dtime)
					q->vars.burst_time -= dtime;
				else
					q->vars.burst_time = 0;
			}
		}
	}
}