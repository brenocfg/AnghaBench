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

/* Variables and functions */
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  multiorder_iteration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multiorder_iteration_race (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multiorder_tagged_iteration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_cpu_dead (int /*<<< orphan*/ ) ; 

void multiorder_checks(void)
{
	multiorder_iteration(&array);
	multiorder_tagged_iteration(&array);
	multiorder_iteration_race(&array);

	radix_tree_cpu_dead(0);
}