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
 int /*<<< orphan*/  RUN_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int,int /*<<< orphan*/ ) ; 
 int ksft_exit_pass () ; 
 int ksft_get_fail_cnt () ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  ksft_test_num () ; 
 int /*<<< orphan*/  sync_api_supported () ; 
 int /*<<< orphan*/  test_alloc_fence ; 
 int /*<<< orphan*/  test_alloc_fence_negative ; 
 int /*<<< orphan*/  test_alloc_timeline ; 
 int /*<<< orphan*/  test_consumer_stress_multi_producer_single_consumer ; 
 int /*<<< orphan*/  test_fence_merge_same_fence ; 
 int /*<<< orphan*/  test_fence_multi_timeline_wait ; 
 int /*<<< orphan*/  test_fence_one_timeline_merge ; 
 int /*<<< orphan*/  test_fence_one_timeline_wait ; 
 int /*<<< orphan*/  test_merge_stress_random_merge ; 
 int /*<<< orphan*/  test_stress_two_threads_shared_timeline ; 

int main(void)
{
	int err;

	ksft_print_header();
	ksft_set_plan(3 + 7);

	sync_api_supported();

	ksft_print_msg("[RUN]\tTesting sync framework\n");

	RUN_TEST(test_alloc_timeline);
	RUN_TEST(test_alloc_fence);
	RUN_TEST(test_alloc_fence_negative);

	RUN_TEST(test_fence_one_timeline_wait);
	RUN_TEST(test_fence_one_timeline_merge);
	RUN_TEST(test_fence_merge_same_fence);
	RUN_TEST(test_fence_multi_timeline_wait);
	RUN_TEST(test_stress_two_threads_shared_timeline);
	RUN_TEST(test_consumer_stress_multi_producer_single_consumer);
	RUN_TEST(test_merge_stress_random_merge);

	err = ksft_get_fail_cnt();
	if (err)
		ksft_exit_fail_msg("%d out of %d sync tests failed\n",
					err, ksft_test_num());

	/* need this return to keep gcc happy */
	return ksft_exit_pass();
}