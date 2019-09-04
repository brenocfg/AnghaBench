#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct us_data {TYPE_2__* current_urb; TYPE_1__* cr; int /*<<< orphan*/  pusb_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  actual_length; } ;
struct TYPE_3__ {void* wLength; void* wIndex; void* wValue; void* bRequest; void* bRequestType; } ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int interpret_urb_result (struct us_data*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,unsigned char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_blocking_completion ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_stor_msg_common (struct us_data*,int /*<<< orphan*/ ) ; 

int usb_stor_ctrl_transfer(struct us_data *us, unsigned int pipe,
		u8 request, u8 requesttype, u16 value, u16 index,
		void *data, u16 size)
{
	int result;

	usb_stor_dbg(us, "rq=%02x rqtype=%02x value=%04x index=%02x len=%u\n",
		     request, requesttype, value, index, size);

	/* fill in the devrequest structure */
	us->cr->bRequestType = requesttype;
	us->cr->bRequest = request;
	us->cr->wValue = cpu_to_le16(value);
	us->cr->wIndex = cpu_to_le16(index);
	us->cr->wLength = cpu_to_le16(size);

	/* fill and submit the URB */
	usb_fill_control_urb(us->current_urb, us->pusb_dev, pipe, 
			 (unsigned char*) us->cr, data, size, 
			 usb_stor_blocking_completion, NULL);
	result = usb_stor_msg_common(us, 0);

	return interpret_urb_result(us, pipe, size, result,
			us->current_urb->actual_length);
}