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
typedef  scalar_t__ u64 ;
struct callchain_root {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int callchain_node_branch_counts_cumul (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

int callchain_branch_counts(struct callchain_root *root,
			    u64 *branch_count, u64 *predicted_count,
			    u64 *abort_count, u64 *cycles_count)
{
	if (branch_count)
		*branch_count = 0;

	if (predicted_count)
		*predicted_count = 0;

	if (abort_count)
		*abort_count = 0;

	if (cycles_count)
		*cycles_count = 0;

	return callchain_node_branch_counts_cumul(&root->node,
						  branch_count,
						  predicted_count,
						  abort_count,
						  cycles_count);
}