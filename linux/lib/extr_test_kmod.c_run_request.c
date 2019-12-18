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
struct test_config {int test_case; int /*<<< orphan*/  test_fs; int /*<<< orphan*/  test_driver; } ;
struct kmod_test_device_info {int need_mod_put; int /*<<< orphan*/  thread_idx; int /*<<< orphan*/ * task_sync; int /*<<< orphan*/  fs_sync; int /*<<< orphan*/  ret_sync; struct kmod_test_device* test_dev; } ;
struct kmod_test_device {int /*<<< orphan*/  thread_mutex; int /*<<< orphan*/  dev; struct test_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  TEST_KMOD_DRIVER 129 
#define  TEST_KMOD_FS_TYPE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fs_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmod_test_done_check (struct kmod_test_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kmod_put_module (struct kmod_test_device_info*) ; 

__attribute__((used)) static int run_request(void *data)
{
	struct kmod_test_device_info *info = data;
	struct kmod_test_device *test_dev = info->test_dev;
	struct test_config *config = &test_dev->config;

	switch (config->test_case) {
	case TEST_KMOD_DRIVER:
		info->ret_sync = request_module("%s", config->test_driver);
		break;
	case TEST_KMOD_FS_TYPE:
		info->fs_sync = get_fs_type(config->test_fs);
		info->need_mod_put = true;
		break;
	default:
		/* __trigger_config_run() already checked for test sanity */
		BUG();
		return -EINVAL;
	}

	dev_dbg(test_dev->dev, "Ran thread %u\n", info->thread_idx);

	test_kmod_put_module(info);

	mutex_lock(&test_dev->thread_mutex);
	info->task_sync = NULL;
	kmod_test_done_check(test_dev, info->thread_idx);
	mutex_unlock(&test_dev->thread_mutex);

	return 0;
}