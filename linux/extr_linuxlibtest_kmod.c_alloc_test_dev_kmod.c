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
struct miscdevice {int /*<<< orphan*/  groups; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct kmod_test_device {int dev_idx; struct miscdevice misc_dev; int /*<<< orphan*/  kthreads_done; int /*<<< orphan*/  thread_mutex; int /*<<< orphan*/  trigger_mutex; int /*<<< orphan*/  config_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  free_test_dev_info (struct kmod_test_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kmod_config_free (struct kmod_test_device*) ; 
 int kmod_config_init (struct kmod_test_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  test_dev_groups ; 
 int /*<<< orphan*/  vfree (struct kmod_test_device*) ; 
 struct kmod_test_device* vzalloc (int) ; 

__attribute__((used)) static struct kmod_test_device *alloc_test_dev_kmod(int idx)
{
	int ret;
	struct kmod_test_device *test_dev;
	struct miscdevice *misc_dev;

	test_dev = vzalloc(sizeof(struct kmod_test_device));
	if (!test_dev)
		goto err_out;

	mutex_init(&test_dev->config_mutex);
	mutex_init(&test_dev->trigger_mutex);
	mutex_init(&test_dev->thread_mutex);

	init_completion(&test_dev->kthreads_done);

	ret = kmod_config_init(test_dev);
	if (ret < 0) {
		pr_err("Cannot alloc kmod_config_init()\n");
		goto err_out_free;
	}

	test_dev->dev_idx = idx;
	misc_dev = &test_dev->misc_dev;

	misc_dev->minor = MISC_DYNAMIC_MINOR;
	misc_dev->name = kasprintf(GFP_KERNEL, "test_kmod%d", idx);
	if (!misc_dev->name) {
		pr_err("Cannot alloc misc_dev->name\n");
		goto err_out_free_config;
	}
	misc_dev->groups = test_dev_groups;

	return test_dev;

err_out_free_config:
	free_test_dev_info(test_dev);
	kmod_config_free(test_dev);
err_out_free:
	vfree(test_dev);
	test_dev = NULL;
err_out:
	return NULL;
}