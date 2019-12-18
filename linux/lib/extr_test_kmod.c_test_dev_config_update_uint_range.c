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
struct kmod_test_device {int /*<<< orphan*/  config_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_dev_config_update_uint_range(struct kmod_test_device *test_dev,
					     const char *buf, size_t size,
					     unsigned int *config,
					     unsigned int min,
					     unsigned int max)
{
	int ret;
	unsigned long new;

	ret = kstrtoul(buf, 10, &new);
	if (ret)
		return ret;

	if (new < min || new > max)
		return -EINVAL;

	mutex_lock(&test_dev->config_mutex);
	*config = new;
	mutex_unlock(&test_dev->config_mutex);

	/* Always return full write size even if we didn't consume all */
	return size;
}