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
struct test_config {int dummy; } ;
struct kmod_test_device {int /*<<< orphan*/  config_mutex; struct test_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kmod_config_free (struct test_config*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kmod_config_free(struct kmod_test_device *test_dev)
{
	struct test_config *config;

	if (!test_dev)
		return;

	config = &test_dev->config;

	mutex_lock(&test_dev->config_mutex);
	__kmod_config_free(config);
	mutex_unlock(&test_dev->config_mutex);
}