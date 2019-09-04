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
struct TYPE_4__ {scalar_t__ length; scalar_t__ actual; scalar_t__ zero; } ;
struct pxa25x_request {TYPE_2__ req; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  desc; } ;
struct pxa25x_ep {unsigned int fifo_size; int /*<<< orphan*/  queue; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,char*,char*,scalar_t__,struct pxa25x_request*) ; 
 int /*<<< orphan*/  DBG_VERY_NOISY ; 
 int UDCCS_BI_TFS ; 
 int /*<<< orphan*/  UDCCS_BI_TPC ; 
 int /*<<< orphan*/  UDCCS_BI_TSP ; 
 int /*<<< orphan*/  done (struct pxa25x_ep*,struct pxa25x_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pio_irq_disable (struct pxa25x_ep*) ; 
 int udc_ep_get_UDCCS (struct pxa25x_ep*) ; 
 int /*<<< orphan*/  udc_ep_set_UDCCS (struct pxa25x_ep*,int /*<<< orphan*/ ) ; 
 int unlikely (int) ; 
 unsigned int usb_endpoint_maxp (int /*<<< orphan*/ ) ; 
 unsigned int write_packet (struct pxa25x_ep*,struct pxa25x_request*,unsigned int) ; 

__attribute__((used)) static int
write_fifo (struct pxa25x_ep *ep, struct pxa25x_request *req)
{
	unsigned		max;

	max = usb_endpoint_maxp(ep->ep.desc);
	do {
		unsigned	count;
		int		is_last, is_short;

		count = write_packet(ep, req, max);

		/* last packet is usually short (or a zlp) */
		if (unlikely (count != max))
			is_last = is_short = 1;
		else {
			if (likely(req->req.length != req->req.actual)
					|| req->req.zero)
				is_last = 0;
			else
				is_last = 1;
			/* interrupt/iso maxpacket may not fill the fifo */
			is_short = unlikely (max < ep->fifo_size);
		}

		DBG(DBG_VERY_NOISY, "wrote %s %d bytes%s%s %d left %p\n",
			ep->ep.name, count,
			is_last ? "/L" : "", is_short ? "/S" : "",
			req->req.length - req->req.actual, req);

		/* let loose that packet. maybe try writing another one,
		 * double buffering might work.  TSP, TPC, and TFS
		 * bit values are the same for all normal IN endpoints.
		 */
		udc_ep_set_UDCCS(ep, UDCCS_BI_TPC);
		if (is_short)
			udc_ep_set_UDCCS(ep, UDCCS_BI_TSP);

		/* requests complete when all IN data is in the FIFO */
		if (is_last) {
			done (ep, req, 0);
			if (list_empty(&ep->queue))
				pio_irq_disable(ep);
			return 1;
		}

		// TODO experiment: how robust can fifo mode tweaking be?
		// double buffering is off in the default fifo mode, which
		// prevents TFS from being set here.

	} while (udc_ep_get_UDCCS(ep) & UDCCS_BI_TFS);
	return 0;
}