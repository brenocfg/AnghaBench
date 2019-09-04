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
struct TYPE_4__ {unsigned int bytes; } ;
struct TYPE_5__ {TYPE_1__ write; } ;
struct pxa25x_udc {scalar_t__ req_pending; TYPE_2__ stats; int /*<<< orphan*/ * ep; } ;
struct TYPE_6__ {unsigned int length; scalar_t__ actual; } ;
struct pxa25x_request {TYPE_3__ req; } ;
struct pxa25x_ep {struct pxa25x_udc* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned int,scalar_t__,struct pxa25x_request*) ; 
 int /*<<< orphan*/  DBG_VERY_NOISY ; 
 unsigned int EP0_FIFO_SIZE ; 
 int UDCCS0_IPR ; 
 int UDCCS0_OPR ; 
 int /*<<< orphan*/  done (struct pxa25x_ep*,struct pxa25x_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_idle (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  ep0start (struct pxa25x_udc*,int,char*) ; 
 int udc_ep0_get_UDCCS (struct pxa25x_udc*) ; 
 int /*<<< orphan*/  udc_ep0_set_UDCCS (struct pxa25x_udc*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int write_packet (int /*<<< orphan*/ *,struct pxa25x_request*,unsigned int) ; 

__attribute__((used)) static int
write_ep0_fifo (struct pxa25x_ep *ep, struct pxa25x_request *req)
{
	struct pxa25x_udc *dev = ep->dev;
	unsigned	count;
	int		is_short;

	count = write_packet(&dev->ep[0], req, EP0_FIFO_SIZE);
	ep->dev->stats.write.bytes += count;

	/* last packet "must be" short (or a zlp) */
	is_short = (count != EP0_FIFO_SIZE);

	DBG(DBG_VERY_NOISY, "ep0in %d bytes %d left %p\n", count,
		req->req.length - req->req.actual, req);

	if (unlikely (is_short)) {
		if (ep->dev->req_pending)
			ep0start(ep->dev, UDCCS0_IPR, "short IN");
		else
			udc_ep0_set_UDCCS(dev, UDCCS0_IPR);

		count = req->req.length;
		done (ep, req, 0);
		ep0_idle(ep->dev);
#ifndef CONFIG_ARCH_IXP4XX
#if 1
		/* This seems to get rid of lost status irqs in some cases:
		 * host responds quickly, or next request involves config
		 * change automagic, or should have been hidden, or ...
		 *
		 * FIXME get rid of all udelays possible...
		 */
		if (count >= EP0_FIFO_SIZE) {
			count = 100;
			do {
				if ((udc_ep0_get_UDCCS(dev) & UDCCS0_OPR) != 0) {
					/* clear OPR, generate ack */
					udc_ep0_set_UDCCS(dev, UDCCS0_OPR);
					break;
				}
				count--;
				udelay(1);
			} while (count);
		}
#endif
#endif
	} else if (ep->dev->req_pending)
		ep0start(ep->dev, 0, "IN");
	return is_short;
}