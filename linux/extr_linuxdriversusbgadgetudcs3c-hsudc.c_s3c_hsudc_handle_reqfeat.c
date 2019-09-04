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
typedef  size_t u8 ;
struct usb_ctrlrequest {scalar_t__ bRequest; size_t wIndex; scalar_t__ bRequestType; int /*<<< orphan*/  wValue; } ;
struct s3c_hsudc_ep {int /*<<< orphan*/  ep; int /*<<< orphan*/  wedge; } ;
struct s3c_hsudc {struct s3c_hsudc_ep* ep; } ;

/* Variables and functions */
 int ENOENT ; 
#define  USB_ENDPOINT_HALT 128 
 size_t USB_ENDPOINT_NUMBER_MASK ; 
 scalar_t__ USB_RECIP_ENDPOINT ; 
 scalar_t__ USB_REQ_SET_FEATURE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hsudc_set_halt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int s3c_hsudc_handle_reqfeat(struct s3c_hsudc *hsudc,
					struct usb_ctrlrequest *ctrl)
{
	struct s3c_hsudc_ep *hsep;
	bool set = (ctrl->bRequest == USB_REQ_SET_FEATURE);
	u8 ep_num = ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK;

	if (ctrl->bRequestType == USB_RECIP_ENDPOINT) {
		hsep = &hsudc->ep[ep_num];
		switch (le16_to_cpu(ctrl->wValue)) {
		case USB_ENDPOINT_HALT:
			if (set || !hsep->wedge)
				s3c_hsudc_set_halt(&hsep->ep, set);
			return 0;
		}
	}

	return -ENOENT;
}