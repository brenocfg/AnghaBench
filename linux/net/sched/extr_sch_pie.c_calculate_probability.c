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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_6__ {int qdelay; int qdelay_old; int avg_dq_rate; int prob; int qlen_old; } ;
struct TYPE_5__ {int target; scalar_t__ beta; scalar_t__ alpha; } ;
struct pie_sched_data {TYPE_3__ vars; TYPE_2__ params; } ;
struct TYPE_4__ {int backlog; } ;
struct Qdisc {TYPE_1__ qstats; } ;
typedef  int s64 ;
typedef  int psched_time_t ;

/* Variables and functions */
 int MAX_PROB ; 
 int NSEC_PER_MSEC ; 
 int PIE_SCALE ; 
 int PSCHED_NS2TICKS (int) ; 
 int PSCHED_TICKS_PER_SEC ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  pie_vars_init (TYPE_3__*) ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void calculate_probability(struct Qdisc *sch)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	u32 qlen = sch->qstats.backlog;	/* queue size in bytes */
	psched_time_t qdelay = 0;	/* in pschedtime */
	psched_time_t qdelay_old = q->vars.qdelay;	/* in pschedtime */
	s64 delta = 0;		/* determines the change in probability */
	u64 oldprob;
	u64 alpha, beta;
	u32 power;
	bool update_prob = true;

	q->vars.qdelay_old = q->vars.qdelay;

	if (q->vars.avg_dq_rate > 0)
		qdelay = (qlen << PIE_SCALE) / q->vars.avg_dq_rate;
	else
		qdelay = 0;

	/* If qdelay is zero and qlen is not, it means qlen is very small, less
	 * than dequeue_rate, so we do not update probabilty in this round
	 */
	if (qdelay == 0 && qlen != 0)
		update_prob = false;

	/* In the algorithm, alpha and beta are between 0 and 2 with typical
	 * value for alpha as 0.125. In this implementation, we use values 0-32
	 * passed from user space to represent this. Also, alpha and beta have
	 * unit of HZ and need to be scaled before they can used to update
	 * probability. alpha/beta are updated locally below by scaling down
	 * by 16 to come to 0-2 range.
	 */
	alpha = ((u64)q->params.alpha * (MAX_PROB / PSCHED_TICKS_PER_SEC)) >> 4;
	beta = ((u64)q->params.beta * (MAX_PROB / PSCHED_TICKS_PER_SEC)) >> 4;

	/* We scale alpha and beta differently depending on how heavy the
	 * congestion is. Please see RFC 8033 for details.
	 */
	if (q->vars.prob < MAX_PROB / 10) {
		alpha >>= 1;
		beta >>= 1;

		power = 100;
		while (q->vars.prob < div_u64(MAX_PROB, power) &&
		       power <= 1000000) {
			alpha >>= 2;
			beta >>= 2;
			power *= 10;
		}
	}

	/* alpha and beta should be between 0 and 32, in multiples of 1/16 */
	delta += alpha * (u64)(qdelay - q->params.target);
	delta += beta * (u64)(qdelay - qdelay_old);

	oldprob = q->vars.prob;

	/* to ensure we increase probability in steps of no more than 2% */
	if (delta > (s64)(MAX_PROB / (100 / 2)) &&
	    q->vars.prob >= MAX_PROB / 10)
		delta = (MAX_PROB / 100) * 2;

	/* Non-linear drop:
	 * Tune drop probability to increase quickly for high delays(>= 250ms)
	 * 250ms is derived through experiments and provides error protection
	 */

	if (qdelay > (PSCHED_NS2TICKS(250 * NSEC_PER_MSEC)))
		delta += MAX_PROB / (100 / 2);

	q->vars.prob += delta;

	if (delta > 0) {
		/* prevent overflow */
		if (q->vars.prob < oldprob) {
			q->vars.prob = MAX_PROB;
			/* Prevent normalization error. If probability is at
			 * maximum value already, we normalize it here, and
			 * skip the check to do a non-linear drop in the next
			 * section.
			 */
			update_prob = false;
		}
	} else {
		/* prevent underflow */
		if (q->vars.prob > oldprob)
			q->vars.prob = 0;
	}

	/* Non-linear drop in probability: Reduce drop probability quickly if
	 * delay is 0 for 2 consecutive Tupdate periods.
	 */

	if (qdelay == 0 && qdelay_old == 0 && update_prob)
		/* Reduce drop probability to 98.4% */
		q->vars.prob -= q->vars.prob / 64u;

	q->vars.qdelay = qdelay;
	q->vars.qlen_old = qlen;

	/* We restart the measurement cycle if the following conditions are met
	 * 1. If the delay has been low for 2 consecutive Tupdate periods
	 * 2. Calculated drop probability is zero
	 * 3. We have atleast one estimate for the avg_dq_rate ie.,
	 *    is a non-zero value
	 */
	if ((q->vars.qdelay < q->params.target / 2) &&
	    (q->vars.qdelay_old < q->params.target / 2) &&
	    q->vars.prob == 0 &&
	    q->vars.avg_dq_rate > 0)
		pie_vars_init(&q->vars);
}