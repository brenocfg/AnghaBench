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
struct tb_ctl {int dummy; } ;
struct tb_cfg_result {int err; int /*<<< orphan*/  member_0; } ;
struct tb_cfg_request {struct tb_cfg_result result; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int tb_cfg_request (struct tb_ctl*,struct tb_cfg_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_cfg_request_cancel (struct tb_cfg_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_cfg_request_complete ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

struct tb_cfg_result tb_cfg_request_sync(struct tb_ctl *ctl,
					 struct tb_cfg_request *req,
					 int timeout_msec)
{
	unsigned long timeout = msecs_to_jiffies(timeout_msec);
	struct tb_cfg_result res = { 0 };
	DECLARE_COMPLETION_ONSTACK(done);
	int ret;

	ret = tb_cfg_request(ctl, req, tb_cfg_request_complete, &done);
	if (ret) {
		res.err = ret;
		return res;
	}

	if (!wait_for_completion_timeout(&done, timeout))
		tb_cfg_request_cancel(req, -ETIMEDOUT);

	flush_work(&req->work);

	return req->result;
}