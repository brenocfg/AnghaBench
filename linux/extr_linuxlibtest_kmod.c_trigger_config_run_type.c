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
struct test_config {int test_case; int /*<<< orphan*/ * test_driver; int /*<<< orphan*/ * test_fs; } ;
struct kmod_test_device {int test_is_oom; int /*<<< orphan*/  config_mutex; struct test_config config; } ;
typedef  enum kmod_test_case { ____Placeholder_kmod_test_case } kmod_test_case ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  TEST_KMOD_DRIVER 129 
#define  TEST_KMOD_FS_TYPE 128 
 int config_copy_test_driver_name (struct test_config*,char const*,int) ; 
 int config_copy_test_fs (struct test_config*,char const*,int) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int trigger_config_run (struct kmod_test_device*) ; 

__attribute__((used)) static int trigger_config_run_type(struct kmod_test_device *test_dev,
				   enum kmod_test_case test_case,
				   const char *test_str)
{
	int copied = 0;
	struct test_config *config = &test_dev->config;

	mutex_lock(&test_dev->config_mutex);

	switch (test_case) {
	case TEST_KMOD_DRIVER:
		kfree_const(config->test_driver);
		config->test_driver = NULL;
		copied = config_copy_test_driver_name(config, test_str,
						      strlen(test_str));
		break;
	case TEST_KMOD_FS_TYPE:
		kfree_const(config->test_fs);
		config->test_driver = NULL;
		copied = config_copy_test_fs(config, test_str,
					     strlen(test_str));
		break;
	default:
		mutex_unlock(&test_dev->config_mutex);
		return -EINVAL;
	}

	config->test_case = test_case;

	mutex_unlock(&test_dev->config_mutex);

	if (copied <= 0 || copied != strlen(test_str)) {
		test_dev->test_is_oom = true;
		return -ENOMEM;
	}

	test_dev->test_is_oom = false;

	return trigger_config_run(test_dev);
}