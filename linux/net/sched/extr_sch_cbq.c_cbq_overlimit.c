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
struct cbq_sched_data {scalar_t__ now; scalar_t__ wd_expires; scalar_t__ toplevel; } ;
struct TYPE_2__ {int /*<<< orphan*/  overactions; } ;
struct cbq_class {scalar_t__ undertime; int delayed; int avgidle; int ewma_log; int minidle; struct cbq_class* borrow; TYPE_1__ xstats; scalar_t__ offtime; int /*<<< orphan*/  qdisc; } ;
typedef  scalar_t__ psched_tdiff_t ;

/* Variables and functions */
 scalar_t__ TC_CBQ_MAXLEVEL ; 
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cbq_overlimit(struct cbq_class *cl)
{
	struct cbq_sched_data *q = qdisc_priv(cl->qdisc);
	psched_tdiff_t delay = cl->undertime - q->now;

	if (!cl->delayed) {
		delay += cl->offtime;

		/*
		 * Class goes to sleep, so that it will have no
		 * chance to work avgidle. Let's forgive it 8)
		 *
		 * BTW cbq-2.0 has a crap in this
		 * place, apparently they forgot to shift it by cl->ewma_log.
		 */
		if (cl->avgidle < 0)
			delay -= (-cl->avgidle) - ((-cl->avgidle) >> cl->ewma_log);
		if (cl->avgidle < cl->minidle)
			cl->avgidle = cl->minidle;
		if (delay <= 0)
			delay = 1;
		cl->undertime = q->now + delay;

		cl->xstats.overactions++;
		cl->delayed = 1;
	}
	if (q->wd_expires == 0 || q->wd_expires > delay)
		q->wd_expires = delay;

	/* Dirty work! We must schedule wakeups based on
	 * real available rate, rather than leaf rate,
	 * which may be tiny (even zero).
	 */
	if (q->toplevel == TC_CBQ_MAXLEVEL) {
		struct cbq_class *b;
		psched_tdiff_t base_delay = q->wd_expires;

		for (b = cl->borrow; b; b = b->borrow) {
			delay = b->undertime - q->now;
			if (delay < base_delay) {
				if (delay <= 0)
					delay = 1;
				base_delay = delay;
			}
		}

		q->wd_expires = base_delay;
	}
}