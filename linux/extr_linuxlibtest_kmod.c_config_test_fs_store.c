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
struct test_config {int /*<<< orphan*/ * test_fs; } ;
struct kmod_test_device {int /*<<< orphan*/  config_mutex; struct test_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int config_copy_test_fs (struct test_config*,char const*,size_t) ; 
 struct kmod_test_device* dev_to_test_dev (struct device*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t config_test_fs_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct kmod_test_device *test_dev = dev_to_test_dev(dev);
	struct test_config *config = &test_dev->config;
	int copied;

	mutex_lock(&test_dev->config_mutex);

	kfree_const(config->test_fs);
	config->test_fs = NULL;

	copied = config_copy_test_fs(config, buf, count);
	mutex_unlock(&test_dev->config_mutex);

	return copied;
}