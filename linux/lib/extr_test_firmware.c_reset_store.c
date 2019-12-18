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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __test_firmware_config_free () ; 
 int __test_firmware_config_init () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  test_fw_mutex ; 

__attribute__((used)) static ssize_t reset_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	int ret;

	mutex_lock(&test_fw_mutex);

	__test_firmware_config_free();

	ret = __test_firmware_config_init();
	if (ret < 0) {
		ret = -ENOMEM;
		pr_err("could not alloc settings for config trigger: %d\n",
		       ret);
		goto out;
	}

	pr_info("reset\n");
	ret = count;

out:
	mutex_unlock(&test_fw_mutex);

	return ret;
}