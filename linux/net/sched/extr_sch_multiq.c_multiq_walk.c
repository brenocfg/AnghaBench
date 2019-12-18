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
struct qdisc_walker {int stop; scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct Qdisc*,int,struct qdisc_walker*) ;} ;
struct multiq_sched_data {int bands; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 scalar_t__ stub1 (struct Qdisc*,int,struct qdisc_walker*) ; 

__attribute__((used)) static void multiq_walk(struct Qdisc *sch, struct qdisc_walker *arg)
{
	struct multiq_sched_data *q = qdisc_priv(sch);
	int band;

	if (arg->stop)
		return;

	for (band = 0; band < q->bands; band++) {
		if (arg->count < arg->skip) {
			arg->count++;
			continue;
		}
		if (arg->fn(sch, band + 1, arg) < 0) {
			arg->stop = 1;
			break;
		}
		arg->count++;
	}
}