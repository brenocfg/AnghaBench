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
struct sugov_cpu {unsigned long max; scalar_t__ bw_dl; int /*<<< orphan*/  cpu; } ;
struct rq {int /*<<< orphan*/  rt; } ;

/* Variables and functions */
 unsigned long arch_scale_cpu_capacity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_bw_dl (struct rq*) ; 
 struct rq* cpu_rq (int /*<<< orphan*/ ) ; 
 unsigned long cpu_util_cfs (struct rq*) ; 
 unsigned long cpu_util_dl (struct rq*) ; 
 unsigned long cpu_util_irq (struct rq*) ; 
 scalar_t__ cpu_util_rt (struct rq*) ; 
 unsigned long min (unsigned long,scalar_t__) ; 
 scalar_t__ rt_rq_is_runnable (int /*<<< orphan*/ *) ; 
 unsigned long scale_irq_capacity (unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long sugov_get_util(struct sugov_cpu *sg_cpu)
{
	struct rq *rq = cpu_rq(sg_cpu->cpu);
	unsigned long util, irq, max;

	sg_cpu->max = max = arch_scale_cpu_capacity(NULL, sg_cpu->cpu);
	sg_cpu->bw_dl = cpu_bw_dl(rq);

	if (rt_rq_is_runnable(&rq->rt))
		return max;

	/*
	 * Early check to see if IRQ/steal time saturates the CPU, can be
	 * because of inaccuracies in how we track these -- see
	 * update_irq_load_avg().
	 */
	irq = cpu_util_irq(rq);
	if (unlikely(irq >= max))
		return max;

	/*
	 * Because the time spend on RT/DL tasks is visible as 'lost' time to
	 * CFS tasks and we use the same metric to track the effective
	 * utilization (PELT windows are synchronized) we can directly add them
	 * to obtain the CPU's actual utilization.
	 */
	util = cpu_util_cfs(rq);
	util += cpu_util_rt(rq);

	/*
	 * We do not make cpu_util_dl() a permanent part of this sum because we
	 * want to use cpu_bw_dl() later on, but we need to check if the
	 * CFS+RT+DL sum is saturated (ie. no idle time) such that we select
	 * f_max when there is no idle time.
	 *
	 * NOTE: numerical errors or stop class might cause us to not quite hit
	 * saturation when we should -- something for later.
	 */
	if ((util + cpu_util_dl(rq)) >= max)
		return max;

	/*
	 * There is still idle time; further improve the number by using the
	 * irq metric. Because IRQ/steal time is hidden from the task clock we
	 * need to scale the task numbers:
	 *
	 *              1 - irq
	 *   U' = irq + ------- * U
	 *                max
	 */
	util = scale_irq_capacity(util, irq, max);
	util += irq;

	/*
	 * Bandwidth required by DEADLINE must always be granted while, for
	 * FAIR and RT, we use blocked utilization of IDLE CPUs as a mechanism
	 * to gracefully reduce the frequency when no tasks show up for longer
	 * periods of time.
	 *
	 * Ideally we would like to set bw_dl as min/guaranteed freq and util +
	 * bw_dl as requested freq. However, cpufreq is not yet ready for such
	 * an interface. So, we only do the latter for now.
	 */
	return min(max, util + sg_cpu->bw_dl);
}