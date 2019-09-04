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
struct mem_cgroup {int /*<<< orphan*/  css; } ;
struct TYPE_2__ {unsigned int memcg_nr_pages_over_high; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 struct mem_cgroup* get_mem_cgroup_from_mm (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  reclaim_high (struct mem_cgroup*,unsigned int,int /*<<< orphan*/ ) ; 

void mem_cgroup_handle_over_high(void)
{
	unsigned int nr_pages = current->memcg_nr_pages_over_high;
	struct mem_cgroup *memcg;

	if (likely(!nr_pages))
		return;

	memcg = get_mem_cgroup_from_mm(current->mm);
	reclaim_high(memcg, nr_pages, GFP_KERNEL);
	css_put(&memcg->css);
	current->memcg_nr_pages_over_high = 0;
}