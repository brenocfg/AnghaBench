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
struct test_config {int test_case; } ;
struct kmod_test_device_info {int need_mod_put; TYPE_1__* fs_sync; struct kmod_test_device* test_dev; } ;
struct kmod_test_device {struct test_config config; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  TEST_KMOD_DRIVER 129 
#define  TEST_KMOD_FS_TYPE 128 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_kmod_put_module(struct kmod_test_device_info *info)
{
	struct kmod_test_device *test_dev = info->test_dev;
	struct test_config *config = &test_dev->config;

	if (!info->need_mod_put)
		return;

	switch (config->test_case) {
	case TEST_KMOD_DRIVER:
		break;
	case TEST_KMOD_FS_TYPE:
		if (info && info->fs_sync && info->fs_sync->owner)
			module_put(info->fs_sync->owner);
		break;
	default:
		BUG();
	}

	info->need_mod_put = true;
}