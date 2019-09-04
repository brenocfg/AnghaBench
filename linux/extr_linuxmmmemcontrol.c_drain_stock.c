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
struct memcg_stock_pcp {struct mem_cgroup* cached; int /*<<< orphan*/  nr_pages; } ;
struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  memsw; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_put_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ do_memsw_account () ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drain_stock(struct memcg_stock_pcp *stock)
{
	struct mem_cgroup *old = stock->cached;

	if (stock->nr_pages) {
		page_counter_uncharge(&old->memory, stock->nr_pages);
		if (do_memsw_account())
			page_counter_uncharge(&old->memsw, stock->nr_pages);
		css_put_many(&old->css, stock->nr_pages);
		stock->nr_pages = 0;
	}
	stock->cached = NULL;
}