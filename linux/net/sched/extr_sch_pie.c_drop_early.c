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
struct TYPE_6__ {int prob; scalar_t__ burst_time; int qdelay; int accu_prob; int accu_prob_overflows; } ;
struct TYPE_5__ {int target; scalar_t__ bytemode; } ;
struct pie_sched_data {TYPE_3__ vars; TYPE_2__ params; } ;
struct TYPE_4__ {int backlog; } ;
struct Qdisc {TYPE_1__ qstats; } ;

/* Variables and functions */
 int MAX_PROB ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  prandom_bytes (int*,int) ; 
 int psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct pie_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static bool drop_early(struct Qdisc *sch, u32 packet_size)
{
	struct pie_sched_data *q = qdisc_priv(sch);
	u64 rnd;
	u64 local_prob = q->vars.prob;
	u32 mtu = psched_mtu(qdisc_dev(sch));

	/* If there is still burst allowance left skip random early drop */
	if (q->vars.burst_time > 0)
		return false;

	/* If current delay is less than half of target, and
	 * if drop prob is low already, disable early_drop
	 */
	if ((q->vars.qdelay < q->params.target / 2) &&
	    (q->vars.prob < MAX_PROB / 5))
		return false;

	/* If we have fewer than 2 mtu-sized packets, disable drop_early,
	 * similar to min_th in RED
	 */
	if (sch->qstats.backlog < 2 * mtu)
		return false;

	/* If bytemode is turned on, use packet size to compute new
	 * probablity. Smaller packets will have lower drop prob in this case
	 */
	if (q->params.bytemode && packet_size <= mtu)
		local_prob = (u64)packet_size * div_u64(local_prob, mtu);
	else
		local_prob = q->vars.prob;

	if (local_prob == 0) {
		q->vars.accu_prob = 0;
		q->vars.accu_prob_overflows = 0;
	}

	if (local_prob > MAX_PROB - q->vars.accu_prob)
		q->vars.accu_prob_overflows++;

	q->vars.accu_prob += local_prob;

	if (q->vars.accu_prob_overflows == 0 &&
	    q->vars.accu_prob < (MAX_PROB / 100) * 85)
		return false;
	if (q->vars.accu_prob_overflows == 8 &&
	    q->vars.accu_prob >= MAX_PROB / 2)
		return true;

	prandom_bytes(&rnd, 8);
	if (rnd < local_prob) {
		q->vars.accu_prob = 0;
		q->vars.accu_prob_overflows = 0;
		return true;
	}

	return false;
}