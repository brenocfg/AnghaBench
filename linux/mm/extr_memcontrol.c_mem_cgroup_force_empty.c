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
struct mem_cgroup {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int EINTR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int MEM_CGROUP_RECLAIM_RETRIES ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drain_all_stock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  lru_add_drain_all () ; 
 scalar_t__ page_counter_read (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int try_to_free_mem_cgroup_pages (struct mem_cgroup*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mem_cgroup_force_empty(struct mem_cgroup *memcg)
{
	int nr_retries = MEM_CGROUP_RECLAIM_RETRIES;

	/* we call try-to-free pages for make this cgroup empty */
	lru_add_drain_all();

	drain_all_stock(memcg);

	/* try to free all pages in this cgroup */
	while (nr_retries && page_counter_read(&memcg->memory)) {
		int progress;

		if (signal_pending(current))
			return -EINTR;

		progress = try_to_free_mem_cgroup_pages(memcg, 1,
							GFP_KERNEL, true);
		if (!progress) {
			nr_retries--;
			/* maybe some writeback is necessary */
			congestion_wait(BLK_RW_ASYNC, HZ/10);
		}

	}

	return 0;
}