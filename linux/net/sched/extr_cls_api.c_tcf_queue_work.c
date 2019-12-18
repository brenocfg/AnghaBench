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
typedef  int /*<<< orphan*/  work_func_t ;
struct rcu_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_RCU_WORK (struct rcu_work*,int /*<<< orphan*/ ) ; 
 int queue_rcu_work (int /*<<< orphan*/ ,struct rcu_work*) ; 
 int /*<<< orphan*/  tc_filter_wq ; 

bool tcf_queue_work(struct rcu_work *rwork, work_func_t func)
{
	INIT_RCU_WORK(rwork, func);
	return queue_rcu_work(tc_filter_wq, rwork);
}