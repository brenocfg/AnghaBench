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
struct TYPE_2__ {int /*<<< orphan*/  cgroup; } ;
struct mem_cgroup {TYPE_1__ css; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_cont_cgroup_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void mem_cgroup_print_oom_group(struct mem_cgroup *memcg)
{
	pr_info("Tasks in ");
	pr_cont_cgroup_path(memcg->css.cgroup);
	pr_cont(" are going to be killed due to memory.oom.group set\n");
}