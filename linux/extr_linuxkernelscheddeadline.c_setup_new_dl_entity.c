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
struct sched_dl_entity {int /*<<< orphan*/  dl_runtime; int /*<<< orphan*/  runtime; scalar_t__ dl_deadline; scalar_t__ deadline; scalar_t__ dl_throttled; int /*<<< orphan*/  dl_boosted; } ;
struct rq {int dummy; } ;
struct dl_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct dl_rq* dl_rq_of_se (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  dl_time_before (scalar_t__,scalar_t__) ; 
 scalar_t__ rq_clock (struct rq*) ; 
 struct rq* rq_of_dl_rq (struct dl_rq*) ; 

__attribute__((used)) static inline void setup_new_dl_entity(struct sched_dl_entity *dl_se)
{
	struct dl_rq *dl_rq = dl_rq_of_se(dl_se);
	struct rq *rq = rq_of_dl_rq(dl_rq);

	WARN_ON(dl_se->dl_boosted);
	WARN_ON(dl_time_before(rq_clock(rq), dl_se->deadline));

	/*
	 * We are racing with the deadline timer. So, do nothing because
	 * the deadline timer handler will take care of properly recharging
	 * the runtime and postponing the deadline
	 */
	if (dl_se->dl_throttled)
		return;

	/*
	 * We use the regular wall clock time to set deadlines in the
	 * future; in fact, we must consider execution overheads (time
	 * spent on hardirq context, etc.).
	 */
	dl_se->deadline = rq_clock(rq) + dl_se->dl_deadline;
	dl_se->runtime = dl_se->dl_runtime;
}