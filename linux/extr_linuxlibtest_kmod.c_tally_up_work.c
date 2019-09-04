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
struct test_config {unsigned int num_threads; int test_result; } ;
struct kmod_test_device_info {int dummy; } ;
struct kmod_test_device {int /*<<< orphan*/  thread_mutex; struct kmod_test_device_info* info; int /*<<< orphan*/  dev; struct test_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tally_work_test (struct kmod_test_device_info*) ; 

__attribute__((used)) static void tally_up_work(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;
	struct kmod_test_device_info *info;
	unsigned int idx;
	int err_ret = 0;
	int ret = 0;

	mutex_lock(&test_dev->thread_mutex);

	dev_info(test_dev->dev, "Results:\n");

	for (idx=0; idx < config->num_threads; idx++) {
		info = &test_dev->info[idx];
		ret = tally_work_test(info);
		if (ret)
			err_ret = ret;
	}

	/*
	 * Note: request_module() returns 256 for a module not found even
	 * though modprobe itself returns 1.
	 */
	config->test_result = err_ret;

	mutex_unlock(&test_dev->thread_mutex);
}