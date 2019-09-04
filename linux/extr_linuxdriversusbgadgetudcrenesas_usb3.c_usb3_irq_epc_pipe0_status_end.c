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
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {int dummy; } ;
struct renesas_usb3 {scalar_t__ test_mode; } ;

/* Variables and functions */
 struct renesas_usb3_ep* usb3_get_ep (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 struct renesas_usb3_request* usb3_get_request (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_request_done (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_set_test_mode (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_epc_pipe0_status_end(struct renesas_usb3 *usb3)
{
	struct renesas_usb3_ep *usb3_ep = usb3_get_ep(usb3, 0);
	struct renesas_usb3_request *usb3_req = usb3_get_request(usb3_ep);

	if (usb3_req)
		usb3_request_done(usb3_ep, usb3_req, 0);
	if (usb3->test_mode)
		usb3_set_test_mode(usb3);
}