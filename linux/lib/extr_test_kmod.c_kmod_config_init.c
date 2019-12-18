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
 int __kmod_config_init (struct kmod_test_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmod_config_init(struct kmod_test_device *test_dev)
{
	int ret;

	mutex_lock(&test_dev->config_mutex);
	ret = __kmod_config_init(test_dev);
	mutex_unlock(&test_dev->config_mutex);

	return ret;
}