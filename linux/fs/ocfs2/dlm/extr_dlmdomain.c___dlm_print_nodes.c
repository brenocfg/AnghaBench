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
struct dlm_ctxt {int /*<<< orphan*/  domain_map; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void __dlm_print_nodes(struct dlm_ctxt *dlm)
{
	int node = -1, num = 0;

	assert_spin_locked(&dlm->spinlock);

	printk("( ");
	while ((node = find_next_bit(dlm->domain_map, O2NM_MAX_NODES,
				     node + 1)) < O2NM_MAX_NODES) {
		printk("%d ", node);
		++num;
	}
	printk(") %u nodes\n", num);
}