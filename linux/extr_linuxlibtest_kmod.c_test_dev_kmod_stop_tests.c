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
struct kmod_test_device_info {scalar_t__ need_mod_put; scalar_t__ task_sync; } ;
struct kmod_test_device {int /*<<< orphan*/  thread_mutex; int /*<<< orphan*/  dev; struct kmod_test_device_info* info; struct test_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_kmod_put_module (struct kmod_test_device_info*) ; 

__attribute__((used)) static void test_dev_kmod_stop_tests(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;
	struct kmod_test_device_info *info;
	unsigned int i;

	dev_info(test_dev->dev, "Ending request_module() tests\n");

	mutex_lock(&test_dev->thread_mutex);

	for (i=0; i < config->num_threads; i++) {
		info = &test_dev->info[i];
		if (info->task_sync && !IS_ERR(info->task_sync)) {
			dev_info(test_dev->dev,
				 "Stopping still-running thread %i\n", i);
			kthread_stop(info->task_sync);
		}

		/*
		 * info->task_sync is well protected, it can only be
		 * NULL or a pointer to a struct. If its NULL we either
		 * never ran, or we did and we completed the work. Completed
		 * tasks *always* put the module for us. This is a sanity
		 * check -- just in case.
		 */
		if (info->task_sync && info->need_mod_put)
			test_kmod_put_module(info);
	}

	mutex_unlock(&test_dev->thread_mutex);
}