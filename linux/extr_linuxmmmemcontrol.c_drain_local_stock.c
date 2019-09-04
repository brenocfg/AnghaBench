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
struct work_struct {int dummy; } ;
struct memcg_stock_pcp {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSHING_CACHED_CHARGE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_stock (struct memcg_stock_pcp*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcg_stock ; 
 struct memcg_stock_pcp* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drain_local_stock(struct work_struct *dummy)
{
	struct memcg_stock_pcp *stock;
	unsigned long flags;

	/*
	 * The only protection from memory hotplug vs. drain_stock races is
	 * that we always operate on local CPU stock here with IRQ disabled
	 */
	local_irq_save(flags);

	stock = this_cpu_ptr(&memcg_stock);
	drain_stock(stock);
	clear_bit(FLUSHING_CACHED_CHARGE, &stock->flags);

	local_irq_restore(flags);
}