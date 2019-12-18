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
struct test_config {unsigned int num_threads; } ;
struct kmod_test_device {int test_is_oom; int /*<<< orphan*/  dev; int /*<<< orphan*/  kthreads_done; struct test_config config; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tally_up_work (struct kmod_test_device*) ; 
 int /*<<< orphan*/  test_dev_kmod_stop_tests (struct kmod_test_device*) ; 
 int try_one_request (struct kmod_test_device*,unsigned int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_requests(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;
	unsigned int idx;
	int ret;
	bool any_error = false;

	for (idx=0; idx < config->num_threads; idx++) {
		if (test_dev->test_is_oom) {
			any_error = true;
			break;
		}

		ret = try_one_request(test_dev, idx);
		if (ret) {
			any_error = true;
			break;
		}
	}

	if (!any_error) {
		test_dev->test_is_oom = false;
		dev_info(test_dev->dev,
			 "No errors were found while initializing threads\n");
		wait_for_completion(&test_dev->kthreads_done);
		tally_up_work(test_dev);
	} else {
		test_dev->test_is_oom = true;
		dev_info(test_dev->dev,
			 "At least one thread failed to start, stop all work\n");
		test_dev_kmod_stop_tests(test_dev);
		return -ENOMEM;
	}

	return 0;
}