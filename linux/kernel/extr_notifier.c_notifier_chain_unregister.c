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
struct notifier_block {struct notifier_block* next; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct notifier_block*,struct notifier_block*) ; 

__attribute__((used)) static int notifier_chain_unregister(struct notifier_block **nl,
		struct notifier_block *n)
{
	while ((*nl) != NULL) {
		if ((*nl) == n) {
			rcu_assign_pointer(*nl, n->next);
			return 0;
		}
		nl = &((*nl)->next);
	}
	return -ENOENT;
}