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
struct test_batched_req {size_t idx; int /*<<< orphan*/  completion; scalar_t__ sent; int /*<<< orphan*/ * task; struct device* dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * fw; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {size_t num_requests; int test_result; struct test_batched_req* reqs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  array3_size (int,size_t,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct test_batched_req*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* test_fw_config ; 
 int /*<<< orphan*/  test_fw_mutex ; 
 int /*<<< orphan*/  test_fw_run_batch_request ; 
 struct test_batched_req* vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t trigger_batched_requests_store(struct device *dev,
					      struct device_attribute *attr,
					      const char *buf, size_t count)
{
	struct test_batched_req *req;
	int rc;
	u8 i;

	mutex_lock(&test_fw_mutex);

	test_fw_config->reqs =
		vzalloc(array3_size(sizeof(struct test_batched_req),
				    test_fw_config->num_requests, 2));
	if (!test_fw_config->reqs) {
		rc = -ENOMEM;
		goto out_unlock;
	}

	pr_info("batched sync firmware loading '%s' %u times\n",
		test_fw_config->name, test_fw_config->num_requests);

	for (i = 0; i < test_fw_config->num_requests; i++) {
		req = &test_fw_config->reqs[i];
		req->fw = NULL;
		req->idx = i;
		req->name = test_fw_config->name;
		req->dev = dev;
		init_completion(&req->completion);
		req->task = kthread_run(test_fw_run_batch_request, req,
					     "%s-%u", KBUILD_MODNAME, req->idx);
		if (!req->task || IS_ERR(req->task)) {
			pr_err("Setting up thread %u failed\n", req->idx);
			req->task = NULL;
			rc = -ENOMEM;
			goto out_bail;
		}
	}

	rc = count;

	/*
	 * We require an explicit release to enable more time and delay of
	 * calling release_firmware() to improve our chances of forcing a
	 * batched request. If we instead called release_firmware() right away
	 * then we might miss on an opportunity of having a successful firmware
	 * request pass on the opportunity to be come a batched request.
	 */

out_bail:
	for (i = 0; i < test_fw_config->num_requests; i++) {
		req = &test_fw_config->reqs[i];
		if (req->task || req->sent)
			wait_for_completion(&req->completion);
	}

	/* Override any worker error if we had a general setup error */
	if (rc < 0)
		test_fw_config->test_result = rc;

out_unlock:
	mutex_unlock(&test_fw_mutex);

	return rc;
}