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
struct test_config {int /*<<< orphan*/  test_case; scalar_t__ test_result; int /*<<< orphan*/  num_threads; } ;
struct kmod_test_device {int test_is_oom; struct test_config config; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TEST_START_DRIVER ; 
 int /*<<< orphan*/  TEST_START_TEST_CASE ; 
 int /*<<< orphan*/  TEST_START_TEST_FS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __kmod_config_free (struct test_config*) ; 
 int config_copy_test_driver_name (struct test_config*,int /*<<< orphan*/ ,int) ; 
 int config_copy_test_fs (struct test_config*,int /*<<< orphan*/ ,int) ; 
 int kmod_config_sync_info (struct kmod_test_device*) ; 
 int /*<<< orphan*/  kmod_init_test_thread_limit () ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __kmod_config_init(struct kmod_test_device *test_dev)
{
	struct test_config *config = &test_dev->config;
	int ret = -ENOMEM, copied;

	__kmod_config_free(config);

	copied = config_copy_test_driver_name(config, TEST_START_DRIVER,
					      strlen(TEST_START_DRIVER));
	if (copied != strlen(TEST_START_DRIVER))
		goto err_out;

	copied = config_copy_test_fs(config, TEST_START_TEST_FS,
				     strlen(TEST_START_TEST_FS));
	if (copied != strlen(TEST_START_TEST_FS))
		goto err_out;

	config->num_threads = kmod_init_test_thread_limit();
	config->test_result = 0;
	config->test_case = TEST_START_TEST_CASE;

	ret = kmod_config_sync_info(test_dev);
	if (ret)
		goto err_out;

	test_dev->test_is_oom = false;

	return 0;

err_out:
	test_dev->test_is_oom = true;
	WARN_ON(test_dev->test_is_oom);

	__kmod_config_free(config);

	return ret;
}