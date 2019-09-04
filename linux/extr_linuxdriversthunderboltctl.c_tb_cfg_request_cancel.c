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
struct TYPE_2__ {int err; } ;
struct tb_cfg_request {TYPE_1__ result; int /*<<< orphan*/  work; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_REQUEST_CANCELED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_cfg_request_cancel_queue ; 
 int /*<<< orphan*/  tb_cfg_request_is_active (struct tb_cfg_request*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void tb_cfg_request_cancel(struct tb_cfg_request *req, int err)
{
	set_bit(TB_CFG_REQUEST_CANCELED, &req->flags);
	schedule_work(&req->work);
	wait_event(tb_cfg_request_cancel_queue, !tb_cfg_request_is_active(req));
	req->result.err = err;
}