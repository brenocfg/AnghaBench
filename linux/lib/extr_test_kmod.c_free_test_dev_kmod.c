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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;
struct kmod_test_device {TYPE_1__ misc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_test_dev_info (struct kmod_test_device*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmod_config_free (struct kmod_test_device*) ; 
 int /*<<< orphan*/  vfree (struct kmod_test_device*) ; 

__attribute__((used)) static void free_test_dev_kmod(struct kmod_test_device *test_dev)
{
	if (test_dev) {
		kfree_const(test_dev->misc_dev.name);
		test_dev->misc_dev.name = NULL;
		free_test_dev_info(test_dev);
		kmod_config_free(test_dev);
		vfree(test_dev);
		test_dev = NULL;
	}
}