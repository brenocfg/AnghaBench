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
typedef  int /*<<< orphan*/  u16 ;
struct usb_ctrlrequest {int bRequestType; int bRequest; int /*<<< orphan*/  member_0; } ;
struct s3c_hsudc_ep {int bEndpointAddress; int /*<<< orphan*/  ep; } ;
struct s3c_hsudc {void* ep0state; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; struct s3c_hsudc_ep* ep; } ;
struct TYPE_2__ {int (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 void* DATA_STATE_RECV ; 
 void* DATA_STATE_XMIT ; 
 int /*<<< orphan*/  EPROTO ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
#define  USB_REQ_CLEAR_FEATURE 131 
#define  USB_REQ_GET_STATUS 130 
#define  USB_REQ_SET_ADDRESS 129 
 int USB_REQ_SET_CONFIGURATION ; 
#define  USB_REQ_SET_FEATURE 128 
 int USB_TYPE_MASK ; 
 int USB_TYPE_STANDARD ; 
 void* WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s3c_hsudc_handle_reqfeat (struct s3c_hsudc*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  s3c_hsudc_nuke_ep (struct s3c_hsudc_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hsudc_process_req_status (struct s3c_hsudc*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  s3c_hsudc_read_setup_pkt (struct s3c_hsudc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c_hsudc_set_halt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 

__attribute__((used)) static void s3c_hsudc_process_setup(struct s3c_hsudc *hsudc)
{
	struct s3c_hsudc_ep *hsep = &hsudc->ep[0];
	struct usb_ctrlrequest ctrl = {0};
	int ret;

	s3c_hsudc_nuke_ep(hsep, -EPROTO);
	s3c_hsudc_read_setup_pkt(hsudc, (u16 *)&ctrl);

	if (ctrl.bRequestType & USB_DIR_IN) {
		hsep->bEndpointAddress |= USB_DIR_IN;
		hsudc->ep0state = DATA_STATE_XMIT;
	} else {
		hsep->bEndpointAddress &= ~USB_DIR_IN;
		hsudc->ep0state = DATA_STATE_RECV;
	}

	switch (ctrl.bRequest) {
	case USB_REQ_SET_ADDRESS:
		if (ctrl.bRequestType != (USB_TYPE_STANDARD | USB_RECIP_DEVICE))
			break;
		hsudc->ep0state = WAIT_FOR_SETUP;
		return;

	case USB_REQ_GET_STATUS:
		if ((ctrl.bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
			break;
		s3c_hsudc_process_req_status(hsudc, &ctrl);
		return;

	case USB_REQ_SET_FEATURE:
	case USB_REQ_CLEAR_FEATURE:
		if ((ctrl.bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
			break;
		s3c_hsudc_handle_reqfeat(hsudc, &ctrl);
		hsudc->ep0state = WAIT_FOR_SETUP;
		return;
	}

	if (hsudc->driver) {
		spin_unlock(&hsudc->lock);
		ret = hsudc->driver->setup(&hsudc->gadget, &ctrl);
		spin_lock(&hsudc->lock);

		if (ctrl.bRequest == USB_REQ_SET_CONFIGURATION) {
			hsep->bEndpointAddress &= ~USB_DIR_IN;
			hsudc->ep0state = WAIT_FOR_SETUP;
		}

		if (ret < 0) {
			dev_err(hsudc->dev, "setup failed, returned %d\n",
						ret);
			s3c_hsudc_set_halt(&hsep->ep, 1);
			hsudc->ep0state = WAIT_FOR_SETUP;
			hsep->bEndpointAddress &= ~USB_DIR_IN;
		}
	}
}