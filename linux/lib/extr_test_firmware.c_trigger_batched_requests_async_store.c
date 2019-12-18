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
struct test_batched_req {size_t name; size_t idx; int rc; int sent; int /*<<< orphan*/  completion; int /*<<< orphan*/ * fw; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int num_requests; size_t name; int send_uevent; int test_result; struct test_batched_req* reqs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FW_ACTION_HOTPLUG ; 
 int FW_ACTION_NOHOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,int) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,size_t,struct device*,int /*<<< orphan*/ ,struct test_batched_req*,int /*<<< orphan*/ ) ; 
 TYPE_1__* test_fw_config ; 
 int /*<<< orphan*/  test_fw_mutex ; 
 int /*<<< orphan*/  trigger_batched_cb ; 
 struct test_batched_req* vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
ssize_t trigger_batched_requests_async_store(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct test_batched_req *req;
	bool send_uevent;
	int rc;
	u8 i;

	mutex_lock(&test_fw_mutex);

	test_fw_config->reqs =
		vzalloc(array3_size(sizeof(struct test_batched_req),
				    test_fw_config->num_requests, 2));
	if (!test_fw_config->reqs) {
		rc = -ENOMEM;
		goto out;
	}

	pr_info("batched loading '%s' custom fallback mechanism %u times\n",
		test_fw_config->name, test_fw_config->num_requests);

	send_uevent = test_fw_config->send_uevent ? FW_ACTION_HOTPLUG :
		FW_ACTION_NOHOTPLUG;

	for (i = 0; i < test_fw_config->num_requests; i++) {
		req = &test_fw_config->reqs[i];
		req->name = test_fw_config->name;
		req->fw = NULL;
		req->idx = i;
		init_completion(&req->completion);
		rc = request_firmware_nowait(THIS_MODULE, send_uevent,
					     req->name,
					     dev, GFP_KERNEL, req,
					     trigger_batched_cb);
		if (rc) {
			pr_info("#%u: batched async load failed setup: %d\n",
				i, rc);
			req->rc = rc;
			goto out_bail;
		} else
			req->sent = true;
	}

	rc = count;

out_bail:

	/*
	 * We require an explicit release to enable more time and delay of
	 * calling release_firmware() to improve our chances of forcing a
	 * batched request. If we instead called release_firmware() right away
	 * then we might miss on an opportunity of having a successful firmware
	 * request pass on the opportunity to be come a batched request.
	 */

	for (i = 0; i < test_fw_config->num_requests; i++) {
		req = &test_fw_config->reqs[i];
		if (req->sent)
			wait_for_completion(&req->completion);
	}

	/* Override any worker error if we had a general setup error */
	if (rc < 0)
		test_fw_config->test_result = rc;

out:
	mutex_unlock(&test_fw_mutex);

	return rc;
}