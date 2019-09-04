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
struct test_config {int num_threads; int test_case; char* test_driver; char* test_fs; } ;
struct kmod_test_device {int /*<<< orphan*/  config_mutex; struct test_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 char* dev_name (struct device*) ; 
 struct kmod_test_device* dev_to_test_dev (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,...) ; 
 char* test_case_str (int) ; 

__attribute__((used)) static ssize_t config_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct kmod_test_device *test_dev = dev_to_test_dev(dev);
	struct test_config *config = &test_dev->config;
	int len = 0;

	mutex_lock(&test_dev->config_mutex);

	len += snprintf(buf, PAGE_SIZE,
			"Custom trigger configuration for: %s\n",
			dev_name(dev));

	len += snprintf(buf+len, PAGE_SIZE - len,
			"Number of threads:\t%u\n",
			config->num_threads);

	len += snprintf(buf+len, PAGE_SIZE - len,
			"Test_case:\t%s (%u)\n",
			test_case_str(config->test_case),
			config->test_case);

	if (config->test_driver)
		len += snprintf(buf+len, PAGE_SIZE - len,
				"driver:\t%s\n",
				config->test_driver);
	else
		len += snprintf(buf+len, PAGE_SIZE - len,
				"driver:\tEMPTY\n");

	if (config->test_fs)
		len += snprintf(buf+len, PAGE_SIZE - len,
				"fs:\t%s\n",
				config->test_fs);
	else
		len += snprintf(buf+len, PAGE_SIZE - len,
				"fs:\tEMPTY\n");

	mutex_unlock(&test_dev->config_mutex);

	return len;
}