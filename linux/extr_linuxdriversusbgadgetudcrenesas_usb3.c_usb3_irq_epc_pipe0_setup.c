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
struct usb_ctrlrequest {int dummy; } ;
struct renesas_usb3_ep {scalar_t__ started; } ;
struct renesas_usb3 {int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 
 struct renesas_usb3_ep* usb3_get_ep (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_get_request (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_get_setup_data (struct renesas_usb3*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usb3_handle_standard_request (struct renesas_usb3*,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usb3_p0_con_clear_buffer (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_request_done (struct renesas_usb3_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_set_p0_con_stall (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_epc_pipe0_setup(struct renesas_usb3 *usb3)
{
	struct usb_ctrlrequest ctrl;
	struct renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);

	/* Call giveback function if previous transfer is not completed */
	if (usb3_ep->started)
		usb3_request_done(usb3_ep, usb3_get_request(usb3_ep),
				  -ECONNRESET);

	usb3_p0_con_clear_buffer(usb3);
	usb3_get_setup_data(usb3, &ctrl);
	if (!usb3_handle_standard_request(usb3, &ctrl))
		if (usb3->driver->setup(&usb3->gadget, &ctrl) < 0)
			usb3_set_p0_con_stall(usb3);
}