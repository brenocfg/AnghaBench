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
struct test_batched_req {int /*<<< orphan*/  completion; struct firmware const* fw; int /*<<< orphan*/  idx; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  test_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 TYPE_1__* test_fw_config ; 

__attribute__((used)) static void trigger_batched_cb(const struct firmware *fw, void *context)
{
	struct test_batched_req *req = context;

	if (!req) {
		test_fw_config->test_result = -EINVAL;
		return;
	}

	/* forces *some* batched requests to queue up */
	if (!req->idx)
		ssleep(2);

	req->fw = fw;

	/*
	 * Unfortunately the firmware API gives us nothing other than a null FW
	 * if the firmware was not found on async requests.  Best we can do is
	 * just assume -ENOENT. A better API would pass the actual return
	 * value to the callback.
	 */
	if (!fw && !test_fw_config->test_result)
		test_fw_config->test_result = -ENOENT;

	complete(&req->completion);
}