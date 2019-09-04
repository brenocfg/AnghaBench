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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int actual; unsigned int length; int /*<<< orphan*/  status; scalar_t__* buf; } ;
struct pxa25x_request {TYPE_2__ req; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct pxa25x_ep {TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMSG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int UDCCS0_IPR ; 
 int UDCCS0_OPR ; 
 int UDCCS0_RNE ; 
 scalar_t__ UDDR0 ; 
 int udc_ep_get_UDCCS (struct pxa25x_ep*) ; 
 int /*<<< orphan*/  udc_ep_set_UDCCS (struct pxa25x_ep*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
read_ep0_fifo (struct pxa25x_ep *ep, struct pxa25x_request *req)
{
	u8		*buf, byte;
	unsigned	bufferspace;

	buf = req->req.buf + req->req.actual;
	bufferspace = req->req.length - req->req.actual;

	while (udc_ep_get_UDCCS(ep) & UDCCS0_RNE) {
		byte = (u8) UDDR0;

		if (unlikely (bufferspace == 0)) {
			/* this happens when the driver's buffer
			 * is smaller than what the host sent.
			 * discard the extra data.
			 */
			if (req->req.status != -EOVERFLOW)
				DMSG("%s overflow\n", ep->ep.name);
			req->req.status = -EOVERFLOW;
		} else {
			*buf++ = byte;
			req->req.actual++;
			bufferspace--;
		}
	}

	udc_ep_set_UDCCS(ep, UDCCS0_OPR | UDCCS0_IPR);

	/* completion */
	if (req->req.actual >= req->req.length)
		return 1;

	/* finished that packet.  the next one may be waiting... */
	return 0;
}