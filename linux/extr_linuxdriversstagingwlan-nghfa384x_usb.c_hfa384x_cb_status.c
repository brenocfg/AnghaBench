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
struct TYPE_2__ {int /*<<< orphan*/  cmdresp; } ;
struct hfa384x_usbctlx {scalar_t__ state; int /*<<< orphan*/  usercb_data; int /*<<< orphan*/  (* usercb ) (struct hfa384x*,struct hfa384x_cmdresult*,int /*<<< orphan*/ ) ;TYPE_1__ inbuf; } ;
struct hfa384x_cmdresult {int /*<<< orphan*/  status; } ;
struct hfa384x {int dummy; } ;
typedef  int /*<<< orphan*/  cmdresult ;

/* Variables and functions */
 scalar_t__ CTLX_COMPLETE ; 
 int /*<<< orphan*/  HFA384x_CMD_ERR ; 
 int /*<<< orphan*/  HFA384x_STATUS_RESULT_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hfa384x_cmdresult*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct hfa384x*,struct hfa384x_cmdresult*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbctlx_get_status (int /*<<< orphan*/ *,struct hfa384x_cmdresult*) ; 

__attribute__((used)) static void hfa384x_cb_status(struct hfa384x *hw,
			      const struct hfa384x_usbctlx *ctlx)
{
	if (ctlx->usercb) {
		struct hfa384x_cmdresult cmdresult;

		if (ctlx->state != CTLX_COMPLETE) {
			memset(&cmdresult, 0, sizeof(cmdresult));
			cmdresult.status =
			    HFA384x_STATUS_RESULT_SET(HFA384x_CMD_ERR);
		} else {
			usbctlx_get_status(&ctlx->inbuf.cmdresp, &cmdresult);
		}

		ctlx->usercb(hw, &cmdresult, ctlx->usercb_data);
	}
}