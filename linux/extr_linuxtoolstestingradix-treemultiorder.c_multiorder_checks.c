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
 int RADIX_TREE_MAP_SHIFT ; 
 int /*<<< orphan*/  multiorder_account () ; 
 int /*<<< orphan*/  multiorder_check (unsigned long,int) ; 
 int /*<<< orphan*/  multiorder_insert_bug () ; 
 int /*<<< orphan*/  multiorder_iteration () ; 
 int /*<<< orphan*/  multiorder_iteration_race () ; 
 int /*<<< orphan*/  multiorder_join () ; 
 int /*<<< orphan*/  multiorder_shrink (unsigned long,int) ; 
 int /*<<< orphan*/  multiorder_split () ; 
 int /*<<< orphan*/  multiorder_tag_tests () ; 
 int /*<<< orphan*/  multiorder_tagged_iteration () ; 
 int /*<<< orphan*/  radix_tree_cpu_dead (int /*<<< orphan*/ ) ; 

void multiorder_checks(void)
{
	int i;

	for (i = 0; i < 20; i++) {
		multiorder_check(200, i);
		multiorder_check(0, i);
		multiorder_check((1UL << i) + 1, i);
	}

	for (i = 0; i < 15; i++)
		multiorder_shrink((1UL << (i + RADIX_TREE_MAP_SHIFT)), i);

	multiorder_insert_bug();
	multiorder_tag_tests();
	multiorder_iteration();
	multiorder_tagged_iteration();
	multiorder_join();
	multiorder_split();
	multiorder_account();
	multiorder_iteration_race();

	radix_tree_cpu_dead(0);
}