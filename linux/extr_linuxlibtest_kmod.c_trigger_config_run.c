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
struct test_config {int /*<<< orphan*/  test_result; } ;
struct kmod_test_device {int /*<<< orphan*/  trigger_mutex; int /*<<< orphan*/  config_mutex; int /*<<< orphan*/  dev; struct test_config config; } ;

/* Variables and functions */
 int __trigger_config_run (struct kmod_test_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int trigger_config_run(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;
	int ret;

	mutex_lock(&test_dev->trigger_mutex);
	mutex_lock(&test_dev->config_mutex);

	ret = __trigger_config_run(test_dev);
	if (ret < 0)
		goto out;
	dev_info(test_dev->dev, "General test result: %d\n",
		 config->test_result);

	/*
	 * We must return 0 after a trigger even unless something went
	 * wrong with the setup of the test. If the test setup went fine
	 * then userspace must just check the result of config->test_result.
	 * One issue with relying on the return from a call in the kernel
	 * is if the kernel returns a possitive value using this trigger
	 * will not return the value to userspace, it would be lost.
	 *
	 * By not relying on capturing the return value of tests we are using
	 * through the trigger it also us to run tests with set -e and only
	 * fail when something went wrong with the driver upon trigger
	 * requests.
	 */
	ret = 0;

out:
	mutex_unlock(&test_dev->config_mutex);
	mutex_unlock(&test_dev->trigger_mutex);

	return ret;
}