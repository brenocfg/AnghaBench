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
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_cgroup_free (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_flush_percpu_vmevents (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_flush_percpu_vmstats (struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  memcg_wb_domain_exit (struct mem_cgroup*) ; 

__attribute__((used)) static void mem_cgroup_free(struct mem_cgroup *memcg)
{
	memcg_wb_domain_exit(memcg);
	/*
	 * Flush percpu vmstats and vmevents to guarantee the value correctness
	 * on parent's and all ancestor levels.
	 */
	memcg_flush_percpu_vmstats(memcg, false);
	memcg_flush_percpu_vmevents(memcg);
	__mem_cgroup_free(memcg);
}