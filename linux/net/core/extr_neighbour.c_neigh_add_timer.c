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
struct neighbour {int /*<<< orphan*/  nud_state; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  neigh_hold (struct neighbour*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void neigh_add_timer(struct neighbour *n, unsigned long when)
{
	neigh_hold(n);
	if (unlikely(mod_timer(&n->timer, when))) {
		printk("NEIGH: BUG, double timer add, state is %x\n",
		       n->nud_state);
		dump_stack();
	}
}