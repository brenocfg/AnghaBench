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

/* Variables and functions */
 int /*<<< orphan*/  cap_exit () ; 
 int cap_init () ; 
 int /*<<< orphan*/  fw_mgmt_exit () ; 
 int fw_mgmt_init () ; 
 int /*<<< orphan*/  gb_fw_core_driver ; 
 int greybus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int fw_core_init(void)
{
	int ret;

	ret = fw_mgmt_init();
	if (ret) {
		pr_err("Failed to initialize fw-mgmt core (%d)\n", ret);
		return ret;
	}

	ret = cap_init();
	if (ret) {
		pr_err("Failed to initialize component authentication core (%d)\n",
		       ret);
		goto fw_mgmt_exit;
	}

	ret = greybus_register(&gb_fw_core_driver);
	if (ret)
		goto cap_exit;

	return 0;

cap_exit:
	cap_exit();
fw_mgmt_exit:
	fw_mgmt_exit();

	return ret;
}