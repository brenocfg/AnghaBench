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
struct qe_udc {int ep0_state; int /*<<< orphan*/  dev; struct qe_ep* eps; } ;
struct qe_req {int dummy; } ;
struct qe_ep {int dummy; } ;

/* Variables and functions */
#define  DATA_STATE_NEED_ZLP 132 
#define  DATA_STATE_RECV 131 
#define  DATA_STATE_XMIT 130 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
#define  WAIT_FOR_OUT_STATUS 129 
#define  WAIT_FOR_SETUP 128 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  done (struct qe_ep*,struct qe_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_prime_status (struct qe_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_ep0_stall (struct qe_udc*) ; 

__attribute__((used)) static void ep0_req_complete(struct qe_udc *udc, struct qe_req *req)
{
	struct qe_ep *ep = &udc->eps[0];
	/* because usb and ep's status already been set in ch9setaddress() */

	switch (udc->ep0_state) {
	case DATA_STATE_XMIT:
		done(ep, req, 0);
		/* receive status phase */
		if (ep0_prime_status(udc, USB_DIR_OUT))
			qe_ep0_stall(udc);
		break;

	case DATA_STATE_NEED_ZLP:
		done(ep, req, 0);
		udc->ep0_state = WAIT_FOR_SETUP;
		break;

	case DATA_STATE_RECV:
		done(ep, req, 0);
		/* send status phase */
		if (ep0_prime_status(udc, USB_DIR_IN))
			qe_ep0_stall(udc);
		break;

	case WAIT_FOR_OUT_STATUS:
		done(ep, req, 0);
		udc->ep0_state = WAIT_FOR_SETUP;
		break;

	case WAIT_FOR_SETUP:
		dev_vdbg(udc->dev, "Unexpected interrupt\n");
		break;

	default:
		qe_ep0_stall(udc);
		break;
	}
}