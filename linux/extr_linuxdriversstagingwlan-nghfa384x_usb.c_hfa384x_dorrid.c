#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usbctlx_rrid_completor {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rridresp; } ;
struct TYPE_4__ {void* rid; void* frmlen; void* type; } ;
struct TYPE_5__ {TYPE_1__ rridreq; } ;
struct hfa384x_usbctlx {int outbufsize; int reapable; TYPE_3__ inbuf; void* usercb_data; int /*<<< orphan*/  usercb; int /*<<< orphan*/  cmdcb; TYPE_2__ outbuf; } ;
struct hfa384x {int dummy; } ;
typedef  enum cmd_mode { ____Placeholder_cmd_mode } cmd_mode ;
typedef  int /*<<< orphan*/  ctlx_usercb_t ;
typedef  int /*<<< orphan*/  ctlx_cmdcb_t ;

/* Variables and functions */
 int DOWAIT ; 
 int ENOMEM ; 
 int HFA384x_USB_RRIDREQ ; 
 void* cpu_to_le16 (int) ; 
 int hfa384x_usbctlx_complete_sync (struct hfa384x*,struct hfa384x_usbctlx*,int /*<<< orphan*/ ) ; 
 int hfa384x_usbctlx_submit (struct hfa384x*,struct hfa384x_usbctlx*) ; 
 int /*<<< orphan*/  init_rrid_completor (struct usbctlx_rrid_completor*,int /*<<< orphan*/ *,void*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct hfa384x_usbctlx*) ; 
 struct hfa384x_usbctlx* usbctlx_alloc () ; 

__attribute__((used)) static int
hfa384x_dorrid(struct hfa384x *hw,
	       enum cmd_mode mode,
	       u16 rid,
	       void *riddata,
	       unsigned int riddatalen,
	       ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, void *usercb_data)
{
	int result;
	struct hfa384x_usbctlx *ctlx;

	ctlx = usbctlx_alloc();
	if (!ctlx) {
		result = -ENOMEM;
		goto done;
	}

	/* Initialize the command */
	ctlx->outbuf.rridreq.type = cpu_to_le16(HFA384x_USB_RRIDREQ);
	ctlx->outbuf.rridreq.frmlen =
	    cpu_to_le16(sizeof(ctlx->outbuf.rridreq.rid));
	ctlx->outbuf.rridreq.rid = cpu_to_le16(rid);

	ctlx->outbufsize = sizeof(ctlx->outbuf.rridreq);

	ctlx->reapable = mode;
	ctlx->cmdcb = cmdcb;
	ctlx->usercb = usercb;
	ctlx->usercb_data = usercb_data;

	/* Submit the CTLX */
	result = hfa384x_usbctlx_submit(hw, ctlx);
	if (result != 0) {
		kfree(ctlx);
	} else if (mode == DOWAIT) {
		struct usbctlx_rrid_completor completor;

		result =
		    hfa384x_usbctlx_complete_sync(hw, ctlx,
						  init_rrid_completor
						  (&completor,
						   &ctlx->inbuf.rridresp,
						   riddata, riddatalen));
	}

done:
	return result;
}