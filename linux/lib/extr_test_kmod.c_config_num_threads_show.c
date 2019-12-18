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
struct test_config {int /*<<< orphan*/  num_threads; } ;
struct kmod_test_device {struct test_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct kmod_test_device* dev_to_test_dev (struct device*) ; 
 int /*<<< orphan*/  test_dev_config_show_int (struct kmod_test_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t config_num_threads_show(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct kmod_test_device *test_dev = dev_to_test_dev(dev);
	struct test_config *config = &test_dev->config;

	return test_dev_config_show_int(test_dev, buf, config->num_threads);
}