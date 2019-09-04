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
struct usbhsg_uep {int dummy; } ;
struct usbhsg_recip_handle {int dummy; } ;
struct usbhsg_gpriv {int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int /*<<< orphan*/ * handler; } ;
struct usbhs_irq_state {int dummy; } ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  bRequest; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
#define  NODATA_STATUS_STAGE 136 
#define  READ_DATA_STAGE 135 
#define  READ_STATUS_STAGE 134 
#define  USB_REQ_CLEAR_FEATURE 133 
#define  USB_REQ_GET_STATUS 132 
#define  USB_REQ_SET_FEATURE 131 
 int USB_TYPE_MASK ; 
#define  USB_TYPE_STANDARD 130 
#define  WRITE_DATA_STAGE 129 
#define  WRITE_STATUS_STAGE 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct usbhsg_recip_handle req_clear_feature ; 
 struct usbhsg_recip_handle req_get_status ; 
 struct usbhsg_recip_handle req_set_feature ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usbhs_ctrl_stage_end_handler ; 
 int /*<<< orphan*/  usbhs_dcp_control_transfer_done (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_fifo_pio_pop_handler ; 
 int /*<<< orphan*/  usbhs_fifo_pio_push_handler ; 
 int /*<<< orphan*/  usbhs_pipe_stall (struct usbhs_pipe*) ; 
 int usbhs_status_get_ctrl_stage (struct usbhs_irq_state*) ; 
 int /*<<< orphan*/  usbhs_usbreq_get_val (struct usbhs_priv*,struct usb_ctrlrequest*) ; 
 struct usbhsg_uep* usbhsg_gpriv_to_dcp (struct usbhsg_gpriv*) ; 
 struct device* usbhsg_gpriv_to_dev (struct usbhsg_gpriv*) ; 
 struct usbhsg_gpriv* usbhsg_priv_to_gpriv (struct usbhs_priv*) ; 
 int usbhsg_recip_run_handle (struct usbhs_priv*,struct usbhsg_recip_handle*,struct usb_ctrlrequest*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 

__attribute__((used)) static int usbhsg_irq_ctrl_stage(struct usbhs_priv *priv,
				 struct usbhs_irq_state *irq_state)
{
	struct usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);
	struct usbhsg_uep *dcp = usbhsg_gpriv_to_dcp(gpriv);
	struct usbhs_pipe *pipe = usbhsg_uep_to_pipe(dcp);
	struct device *dev = usbhsg_gpriv_to_dev(gpriv);
	struct usb_ctrlrequest ctrl;
	struct usbhsg_recip_handle *recip_handler = NULL;
	int stage = usbhs_status_get_ctrl_stage(irq_state);
	int ret = 0;

	dev_dbg(dev, "stage = %d\n", stage);

	/*
	 * see Manual
	 *
	 *  "Operation"
	 *  - "Interrupt Function"
	 *    - "Control Transfer Stage Transition Interrupt"
	 *      - Fig. "Control Transfer Stage Transitions"
	 */

	switch (stage) {
	case READ_DATA_STAGE:
		pipe->handler = &usbhs_fifo_pio_push_handler;
		break;
	case WRITE_DATA_STAGE:
		pipe->handler = &usbhs_fifo_pio_pop_handler;
		break;
	case NODATA_STATUS_STAGE:
		pipe->handler = &usbhs_ctrl_stage_end_handler;
		break;
	case READ_STATUS_STAGE:
	case WRITE_STATUS_STAGE:
		usbhs_dcp_control_transfer_done(pipe);
		/* fall through */
	default:
		return ret;
	}

	/*
	 * get usb request
	 */
	usbhs_usbreq_get_val(priv, &ctrl);

	switch (ctrl.bRequestType & USB_TYPE_MASK) {
	case USB_TYPE_STANDARD:
		switch (ctrl.bRequest) {
		case USB_REQ_CLEAR_FEATURE:
			recip_handler = &req_clear_feature;
			break;
		case USB_REQ_SET_FEATURE:
			recip_handler = &req_set_feature;
			break;
		case USB_REQ_GET_STATUS:
			recip_handler = &req_get_status;
			break;
		}
	}

	/*
	 * setup stage / run recip
	 */
	if (recip_handler)
		ret = usbhsg_recip_run_handle(priv, recip_handler, &ctrl);
	else
		ret = gpriv->driver->setup(&gpriv->gadget, &ctrl);

	if (ret < 0)
		usbhs_pipe_stall(pipe);

	return ret;
}