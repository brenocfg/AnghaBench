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
 int /*<<< orphan*/  run_parallel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_arraymap ; 
 int /*<<< orphan*/  test_arraymap_percpu ; 
 int /*<<< orphan*/  test_hashmap ; 
 int /*<<< orphan*/  test_hashmap_percpu ; 
 int /*<<< orphan*/  test_hashmap_sizes ; 
 int /*<<< orphan*/  test_hashmap_walk ; 

__attribute__((used)) static void test_map_stress(void)
{
	run_parallel(100, test_hashmap, NULL);
	run_parallel(100, test_hashmap_percpu, NULL);
	run_parallel(100, test_hashmap_sizes, NULL);
	run_parallel(100, test_hashmap_walk, NULL);

	run_parallel(100, test_arraymap, NULL);
	run_parallel(100, test_arraymap_percpu, NULL);
}