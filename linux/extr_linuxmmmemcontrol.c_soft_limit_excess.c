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
struct mem_cgroup {int /*<<< orphan*/  soft_limit; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long page_counter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long soft_limit_excess(struct mem_cgroup *memcg)
{
	unsigned long nr_pages = page_counter_read(&memcg->memory);
	unsigned long soft_limit = READ_ONCE(memcg->soft_limit);
	unsigned long excess = 0;

	if (nr_pages > soft_limit)
		excess = nr_pages - soft_limit;

	return excess;
}