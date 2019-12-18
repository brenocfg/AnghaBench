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
struct kmod_test_device_info {unsigned int thread_idx; int ret_sync; int /*<<< orphan*/ * task_sync; struct kmod_test_device* test_dev; } ;
struct kmod_test_device {int test_is_oom; int /*<<< orphan*/  thread_mutex; int /*<<< orphan*/  dev; struct kmod_test_device_info* info; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct kmod_test_device_info*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_request ; 

__attribute__((used)) static int try_one_request(struct kmod_test_device *test_dev, unsigned int idx)
{
	struct kmod_test_device_info *info = &test_dev->info[idx];
	int fail_ret = -ENOMEM;

	mutex_lock(&test_dev->thread_mutex);

	info->thread_idx = idx;
	info->test_dev = test_dev;
	info->task_sync = kthread_run(run_request, info, "%s-%u",
				      KBUILD_MODNAME, idx);

	if (!info->task_sync || IS_ERR(info->task_sync)) {
		test_dev->test_is_oom = true;
		dev_err(test_dev->dev, "Setting up thread %u failed\n", idx);
		info->task_sync = NULL;
		goto err_out;
	} else
		dev_dbg(test_dev->dev, "Kicked off thread %u\n", idx);

	mutex_unlock(&test_dev->thread_mutex);

	return 0;

err_out:
	info->ret_sync = fail_ret;
	mutex_unlock(&test_dev->thread_mutex);

	return fail_ret;
}