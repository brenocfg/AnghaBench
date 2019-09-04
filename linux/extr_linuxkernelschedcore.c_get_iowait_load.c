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
struct TYPE_2__ {unsigned long weight; } ;
struct rq {TYPE_1__ load; int /*<<< orphan*/  nr_iowait; } ;

/* Variables and functions */
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 
 struct rq* this_rq () ; 

void get_iowait_load(unsigned long *nr_waiters, unsigned long *load)
{
	struct rq *rq = this_rq();
	*nr_waiters = atomic_read(&rq->nr_iowait);
	*load = rq->load.weight;
}