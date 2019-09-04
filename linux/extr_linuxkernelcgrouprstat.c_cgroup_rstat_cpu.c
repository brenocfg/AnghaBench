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
struct cgroup_rstat_cpu {int dummy; } ;
struct cgroup {int /*<<< orphan*/  rstat_cpu; } ;

/* Variables and functions */
 struct cgroup_rstat_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cgroup_rstat_cpu *cgroup_rstat_cpu(struct cgroup *cgrp, int cpu)
{
	return per_cpu_ptr(cgrp->rstat_cpu, cpu);
}