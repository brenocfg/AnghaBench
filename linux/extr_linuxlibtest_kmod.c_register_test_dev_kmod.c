#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  this_device; } ;
struct kmod_test_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; TYPE_1__ misc_dev; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 struct kmod_test_device* alloc_test_dev_kmod (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_test_dev_kmod (struct kmod_test_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int misc_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ num_test_devs ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  reg_dev_mutex ; 
 int /*<<< orphan*/  reg_test_devs ; 

__attribute__((used)) static struct kmod_test_device *register_test_dev_kmod(void)
{
	struct kmod_test_device *test_dev = NULL;
	int ret;

	mutex_lock(&reg_dev_mutex);

	/* int should suffice for number of devices, test for wrap */
	if (num_test_devs + 1 == INT_MAX) {
		pr_err("reached limit of number of test devices\n");
		goto out;
	}

	test_dev = alloc_test_dev_kmod(num_test_devs);
	if (!test_dev)
		goto out;

	ret = misc_register(&test_dev->misc_dev);
	if (ret) {
		pr_err("could not register misc device: %d\n", ret);
		free_test_dev_kmod(test_dev);
		goto out;
	}

	test_dev->dev = test_dev->misc_dev.this_device;
	list_add_tail(&test_dev->list, &reg_test_devs);
	dev_info(test_dev->dev, "interface ready\n");

	num_test_devs++;

out:
	mutex_unlock(&reg_dev_mutex);

	return test_dev;

}