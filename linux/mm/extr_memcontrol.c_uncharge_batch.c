#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct uncharge_gather {unsigned long nr_anon; unsigned long nr_file; unsigned long nr_kmem; unsigned long nr_huge; unsigned long nr_shmem; TYPE_2__* memcg; int /*<<< orphan*/  dummy_page; int /*<<< orphan*/  pgpgout; } ;
struct TYPE_8__ {int /*<<< orphan*/  css; TYPE_1__* vmstats_percpu; int /*<<< orphan*/  kmem; int /*<<< orphan*/  memsw; int /*<<< orphan*/  memory; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr_page_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_CACHE ; 
 int /*<<< orphan*/  MEMCG_RSS ; 
 int /*<<< orphan*/  MEMCG_RSS_HUGE ; 
 int /*<<< orphan*/  NR_SHMEM ; 
 int /*<<< orphan*/  PGPGOUT ; 
 int /*<<< orphan*/  __count_memcg_events (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_memcg_state (TYPE_2__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_put_many (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ do_memsw_account () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mem_cgroup_is_root (TYPE_2__*) ; 
 int /*<<< orphan*/  memcg_check_events (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcg_oom_recover (TYPE_2__*) ; 
 int /*<<< orphan*/  memory_cgrp_subsys ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void uncharge_batch(const struct uncharge_gather *ug)
{
	unsigned long nr_pages = ug->nr_anon + ug->nr_file + ug->nr_kmem;
	unsigned long flags;

	if (!mem_cgroup_is_root(ug->memcg)) {
		page_counter_uncharge(&ug->memcg->memory, nr_pages);
		if (do_memsw_account())
			page_counter_uncharge(&ug->memcg->memsw, nr_pages);
		if (!cgroup_subsys_on_dfl(memory_cgrp_subsys) && ug->nr_kmem)
			page_counter_uncharge(&ug->memcg->kmem, ug->nr_kmem);
		memcg_oom_recover(ug->memcg);
	}

	local_irq_save(flags);
	__mod_memcg_state(ug->memcg, MEMCG_RSS, -ug->nr_anon);
	__mod_memcg_state(ug->memcg, MEMCG_CACHE, -ug->nr_file);
	__mod_memcg_state(ug->memcg, MEMCG_RSS_HUGE, -ug->nr_huge);
	__mod_memcg_state(ug->memcg, NR_SHMEM, -ug->nr_shmem);
	__count_memcg_events(ug->memcg, PGPGOUT, ug->pgpgout);
	__this_cpu_add(ug->memcg->vmstats_percpu->nr_page_events, nr_pages);
	memcg_check_events(ug->memcg, ug->dummy_page);
	local_irq_restore(flags);

	if (!mem_cgroup_is_root(ug->memcg))
		css_put_many(&ug->memcg->css, nr_pages);
}