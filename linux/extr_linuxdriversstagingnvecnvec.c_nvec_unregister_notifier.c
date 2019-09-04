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
struct nvec_chip {int /*<<< orphan*/  notifier_list; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int atomic_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 

int nvec_unregister_notifier(struct nvec_chip *nvec, struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&nvec->notifier_list, nb);
}