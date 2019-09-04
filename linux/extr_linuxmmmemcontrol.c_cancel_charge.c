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
struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  memsw; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_put_many (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ do_memsw_account () ; 
 scalar_t__ mem_cgroup_is_root (struct mem_cgroup*) ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void cancel_charge(struct mem_cgroup *memcg, unsigned int nr_pages)
{
	if (mem_cgroup_is_root(memcg))
		return;

	page_counter_uncharge(&memcg->memory, nr_pages);
	if (do_memsw_account())
		page_counter_uncharge(&memcg->memsw, nr_pages);

	css_put_many(&memcg->css, nr_pages);
}