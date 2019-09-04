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
struct notifier_block {int dummy; } ;
struct blocking_notifier_head {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int notifier_chain_cond_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int blocking_notifier_chain_cond_register(struct blocking_notifier_head *nh,
		struct notifier_block *n)
{
	int ret;

	down_write(&nh->rwsem);
	ret = notifier_chain_cond_register(&nh->head, n);
	up_write(&nh->rwsem);
	return ret;
}