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

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  atomic_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  fib_chain ; 
 unsigned int fib_seq_sum () ; 

__attribute__((used)) static bool fib_dump_is_consistent(struct notifier_block *nb,
				   void (*cb)(struct notifier_block *nb),
				   unsigned int fib_seq)
{
	atomic_notifier_chain_register(&fib_chain, nb);
	if (fib_seq == fib_seq_sum())
		return true;
	atomic_notifier_chain_unregister(&fib_chain, nb);
	if (cb)
		cb(nb);
	return false;
}