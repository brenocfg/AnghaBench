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
struct sugov_cpu {unsigned long max; int /*<<< orphan*/  cpu; int /*<<< orphan*/  bw_dl; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQUENCY_UTIL ; 
 unsigned long arch_scale_cpu_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_bw_dl (struct rq*) ; 
 struct rq* cpu_rq (int /*<<< orphan*/ ) ; 
 unsigned long cpu_util_cfs (struct rq*) ; 
 unsigned long schedutil_cpu_util (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long sugov_get_util(struct sugov_cpu *sg_cpu)
{
	struct rq *rq = cpu_rq(sg_cpu->cpu);
	unsigned long util = cpu_util_cfs(rq);
	unsigned long max = arch_scale_cpu_capacity(sg_cpu->cpu);

	sg_cpu->max = max;
	sg_cpu->bw_dl = cpu_bw_dl(rq);

	return schedutil_cpu_util(sg_cpu->cpu, util, max, FREQUENCY_UTIL, NULL);
}