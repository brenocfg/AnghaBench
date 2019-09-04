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

/* Variables and functions */
 int /*<<< orphan*/  __test_release_all_firmware () ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ *) ; 
 TYPE_1__* test_fw_config ; 

__attribute__((used)) static void __test_firmware_config_free(void)
{
	__test_release_all_firmware();
	kfree_const(test_fw_config->name);
	test_fw_config->name = NULL;
}