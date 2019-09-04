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
struct rq {int /*<<< orphan*/  calc_load_update; } ;

/* Variables and functions */
 scalar_t__ LOAD_FREQ ; 
 int /*<<< orphan*/  atomic_long_add (long,int /*<<< orphan*/ *) ; 
 long calc_load_fold_active (struct rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_load_tasks ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void calc_global_load_tick(struct rq *this_rq)
{
	long delta;

	if (time_before(jiffies, this_rq->calc_load_update))
		return;

	delta  = calc_load_fold_active(this_rq, 0);
	if (delta)
		atomic_long_add(delta, &calc_load_tasks);

	this_rq->calc_load_update += LOAD_FREQ;
}