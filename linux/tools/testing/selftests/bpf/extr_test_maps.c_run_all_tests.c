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
 int /*<<< orphan*/  test_arraymap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_arraymap_percpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_arraymap_percpu_many_keys () ; 
 int /*<<< orphan*/  test_devmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_devmap_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_hashmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_hashmap_percpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_hashmap_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_hashmap_zero_seed () ; 
 int /*<<< orphan*/  test_map_in_map () ; 
 int /*<<< orphan*/  test_map_large () ; 
 int /*<<< orphan*/  test_map_parallel () ; 
 int /*<<< orphan*/  test_map_rdonly () ; 
 int /*<<< orphan*/  test_map_stress () ; 
 int /*<<< orphan*/  test_map_wronly () ; 
 int /*<<< orphan*/  test_queuemap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_reuseport_array () ; 
 int /*<<< orphan*/  test_sockmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_stackmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void run_all_tests(void)
{
	test_hashmap(0, NULL);
	test_hashmap_percpu(0, NULL);
	test_hashmap_walk(0, NULL);
	test_hashmap_zero_seed();

	test_arraymap(0, NULL);
	test_arraymap_percpu(0, NULL);

	test_arraymap_percpu_many_keys();

	test_devmap(0, NULL);
	test_devmap_hash(0, NULL);
	test_sockmap(0, NULL);

	test_map_large();
	test_map_parallel();
	test_map_stress();

	test_map_rdonly();
	test_map_wronly();

	test_reuseport_array();

	test_queuemap(0, NULL);
	test_stackmap(0, NULL);

	test_map_in_map();
}