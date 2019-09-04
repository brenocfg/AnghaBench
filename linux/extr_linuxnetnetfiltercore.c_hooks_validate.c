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
struct nf_hook_entries {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hooks_validate(const struct nf_hook_entries *hooks)
{
#ifdef CONFIG_DEBUG_KERNEL
	struct nf_hook_ops **orig_ops;
	int prio = INT_MIN;
	size_t i = 0;

	orig_ops = nf_hook_entries_get_hook_ops(hooks);

	for (i = 0; i < hooks->num_hook_entries; i++) {
		if (orig_ops[i] == &dummy_ops)
			continue;

		WARN_ON(orig_ops[i]->priority < prio);

		if (orig_ops[i]->priority > prio)
			prio = orig_ops[i]->priority;
	}
#endif
}