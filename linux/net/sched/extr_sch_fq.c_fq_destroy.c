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
struct fq_sched_data {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  fq_root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_reset (struct Qdisc*) ; 
 struct fq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fq_destroy(struct Qdisc *sch)
{
	struct fq_sched_data *q = qdisc_priv(sch);

	fq_reset(sch);
	fq_free(q->fq_root);
	qdisc_watchdog_cancel(&q->watchdog);
}