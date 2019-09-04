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
typedef  size_t u8 ;
struct test_batched_req {scalar_t__ fw; } ;
struct TYPE_2__ {size_t num_requests; struct test_batched_req* reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 TYPE_1__* test_fw_config ; 
 int /*<<< orphan*/  vfree (struct test_batched_req*) ; 

__attribute__((used)) static void __test_release_all_firmware(void)
{
	struct test_batched_req *req;
	u8 i;

	if (!test_fw_config->reqs)
		return;

	for (i = 0; i < test_fw_config->num_requests; i++) {
		req = &test_fw_config->reqs[i];
		if (req->fw)
			release_firmware(req->fw);
	}

	vfree(test_fw_config->reqs);
	test_fw_config->reqs = NULL;
}