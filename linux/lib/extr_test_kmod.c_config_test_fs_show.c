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
struct test_config {int /*<<< orphan*/  test_fs; } ;
struct kmod_test_device {int /*<<< orphan*/  config_mutex; struct test_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_test_show_str (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct kmod_test_device* dev_to_test_dev (struct device*) ; 

__attribute__((used)) static ssize_t config_test_fs_show(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct kmod_test_device *test_dev = dev_to_test_dev(dev);
	struct test_config *config = &test_dev->config;

	return config_test_show_str(&test_dev->config_mutex, buf,
				    config->test_fs);
}