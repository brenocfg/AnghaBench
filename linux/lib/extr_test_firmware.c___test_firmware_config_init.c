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
struct TYPE_2__ {int send_uevent; int into_buf; int sync_direct; int /*<<< orphan*/ * reqs; scalar_t__ test_result; int /*<<< orphan*/  req_firmware; int /*<<< orphan*/  num_requests; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TEST_FIRMWARE_NAME ; 
 int /*<<< orphan*/  TEST_FIRMWARE_NUM_REQS ; 
 int __kstrncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_firmware_config_free () ; 
 int /*<<< orphan*/  request_firmware ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 TYPE_1__* test_fw_config ; 

__attribute__((used)) static int __test_firmware_config_init(void)
{
	int ret;

	ret = __kstrncpy(&test_fw_config->name, TEST_FIRMWARE_NAME,
			 strlen(TEST_FIRMWARE_NAME), GFP_KERNEL);
	if (ret < 0)
		goto out;

	test_fw_config->num_requests = TEST_FIRMWARE_NUM_REQS;
	test_fw_config->send_uevent = true;
	test_fw_config->into_buf = false;
	test_fw_config->sync_direct = false;
	test_fw_config->req_firmware = request_firmware;
	test_fw_config->test_result = 0;
	test_fw_config->reqs = NULL;

	return 0;

out:
	__test_firmware_config_free();
	return ret;
}