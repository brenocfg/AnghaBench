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
struct worker_pool {scalar_t__ node; TYPE_1__* attrs; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  nice; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 scalar_t__ NUMA_NO_NODE ; 
 int /*<<< orphan*/  nr_cpumask_bits ; 
 int /*<<< orphan*/  pr_cont (char*,scalar_t__,...) ; 

__attribute__((used)) static void pr_cont_pool_info(struct worker_pool *pool)
{
	pr_cont(" cpus=%*pbl", nr_cpumask_bits, pool->attrs->cpumask);
	if (pool->node != NUMA_NO_NODE)
		pr_cont(" node=%d", pool->node);
	pr_cont(" flags=0x%x nice=%d", pool->flags, pool->attrs->nice);
}