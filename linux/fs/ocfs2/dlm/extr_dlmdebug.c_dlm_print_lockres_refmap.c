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
struct dlm_lock_resource {int inflight_locks; int /*<<< orphan*/  refmap; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void dlm_print_lockres_refmap(struct dlm_lock_resource *res)
{
	int bit;
	assert_spin_locked(&res->spinlock);

	printk("  refmap nodes: [ ");
	bit = 0;
	while (1) {
		bit = find_next_bit(res->refmap, O2NM_MAX_NODES, bit);
		if (bit >= O2NM_MAX_NODES)
			break;
		printk("%u ", bit);
		bit++;
	}
	printk("], inflight=%u\n", res->inflight_locks);
}