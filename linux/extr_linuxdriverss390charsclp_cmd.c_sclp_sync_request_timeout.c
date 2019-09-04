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
struct sclp_req {int queue_timeout; scalar_t__ status; struct completion* callback_data; int /*<<< orphan*/  callback; void* sccb; int /*<<< orphan*/  command; } ;
struct completion {int dummy; } ;
typedef  int /*<<< orphan*/  sclp_cmdw_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SCLP_REQ_DONE ; 
 scalar_t__ SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  kfree (struct sclp_req*) ; 
 struct sclp_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sclp_add_request (struct sclp_req*) ; 
 int /*<<< orphan*/  sclp_sync_callback ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

int sclp_sync_request_timeout(sclp_cmdw_t cmd, void *sccb, int timeout)
{
	struct completion completion;
	struct sclp_req *request;
	int rc;

	request = kzalloc(sizeof(*request), GFP_KERNEL);
	if (!request)
		return -ENOMEM;
	if (timeout)
		request->queue_timeout = timeout;
	request->command = cmd;
	request->sccb = sccb;
	request->status = SCLP_REQ_FILLED;
	request->callback = sclp_sync_callback;
	request->callback_data = &completion;
	init_completion(&completion);

	/* Perform sclp request. */
	rc = sclp_add_request(request);
	if (rc)
		goto out;
	wait_for_completion(&completion);

	/* Check response. */
	if (request->status != SCLP_REQ_DONE) {
		pr_warn("sync request failed (cmd=0x%08x, status=0x%02x)\n",
			cmd, request->status);
		rc = -EIO;
	}
out:
	kfree(request);
	return rc;
}