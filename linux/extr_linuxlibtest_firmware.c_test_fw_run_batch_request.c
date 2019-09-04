#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct test_batched_req {int rc; int sent; int /*<<< orphan*/ * task; int /*<<< orphan*/  completion; TYPE_2__* fw; int /*<<< orphan*/  idx; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int size; } ;
struct TYPE_3__ {int test_result; int (* req_firmware ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* test_fw_config ; 

__attribute__((used)) static int test_fw_run_batch_request(void *data)
{
	struct test_batched_req *req = data;

	if (!req) {
		test_fw_config->test_result = -EINVAL;
		return -EINVAL;
	}

	req->rc = test_fw_config->req_firmware(&req->fw, req->name, req->dev);
	if (req->rc) {
		pr_info("#%u: batched sync load failed: %d\n",
			req->idx, req->rc);
		if (!test_fw_config->test_result)
			test_fw_config->test_result = req->rc;
	} else if (req->fw) {
		req->sent = true;
		pr_info("#%u: batched sync loaded %zu\n",
			req->idx, req->fw->size);
	}
	complete(&req->completion);

	req->task = NULL;

	return 0;
}