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
struct memcg_stock_pcp {unsigned int nr_pages; struct mem_cgroup* cached; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 unsigned int MEMCG_CHARGE_BATCH ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcg_stock ; 
 struct memcg_stock_pcp* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool consume_stock(struct mem_cgroup *memcg, unsigned int nr_pages)
{
	struct memcg_stock_pcp *stock;
	unsigned long flags;
	bool ret = false;

	if (nr_pages > MEMCG_CHARGE_BATCH)
		return ret;

	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	if (memcg == stock->cached && stock->nr_pages >= nr_pages) {
		stock->nr_pages -= nr_pages;
		ret = true;
	}

	local_irq_restore(flags);

	return ret;
}