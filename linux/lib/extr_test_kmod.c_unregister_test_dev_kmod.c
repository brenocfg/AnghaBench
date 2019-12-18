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
struct kmod_test_device {int /*<<< orphan*/  trigger_mutex; int /*<<< orphan*/  config_mutex; int /*<<< orphan*/  misc_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_test_dev_kmod (struct kmod_test_device*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_dev_kmod_stop_tests (struct kmod_test_device*) ; 

__attribute__((used)) static
void unregister_test_dev_kmod(struct kmod_test_device *test_dev)
{
	mutex_lock(&test_dev->trigger_mutex);
	mutex_lock(&test_dev->config_mutex);

	test_dev_kmod_stop_tests(test_dev);

	dev_info(test_dev->dev, "removing interface\n");
	misc_deregister(&test_dev->misc_dev);

	mutex_unlock(&test_dev->config_mutex);
	mutex_unlock(&test_dev->trigger_mutex);

	free_test_dev_kmod(test_dev);
}