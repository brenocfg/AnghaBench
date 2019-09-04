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
struct se_device {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strstr (char const*,char*) ; 
 int target_configure_device (struct se_device*) ; 
 struct se_device* to_device (struct config_item*) ; 

__attribute__((used)) static ssize_t target_dev_enable_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_device *dev = to_device(item);
	char *ptr;
	int ret;

	ptr = strstr(page, "1");
	if (!ptr) {
		pr_err("For dev_enable ops, only valid value"
				" is \"1\"\n");
		return -EINVAL;
	}

	ret = target_configure_device(dev);
	if (ret)
		return ret;
	return count;
}