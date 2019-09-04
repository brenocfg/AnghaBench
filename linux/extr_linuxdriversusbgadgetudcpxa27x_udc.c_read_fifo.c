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
struct pxa_ep {int fifo_size; } ;
struct TYPE_2__ {scalar_t__ actual; scalar_t__ length; } ;
struct pxa27x_request {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCSR ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  ep_dbg (struct pxa_ep*,char*,int /*<<< orphan*/ ,int,char*,TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ epout_has_pkt (struct pxa_ep*) ; 
 int /*<<< orphan*/  inc_ep_stats_bytes (struct pxa_ep*,int,int) ; 
 int read_packet (struct pxa_ep*,struct pxa27x_request*) ; 
 int /*<<< orphan*/  udc_ep_readl (struct pxa_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_fifo(struct pxa_ep *ep, struct pxa27x_request *req)
{
	int count, is_short, completed = 0;

	while (epout_has_pkt(ep)) {
		count = read_packet(ep, req);
		inc_ep_stats_bytes(ep, count, !USB_DIR_IN);

		is_short = (count < ep->fifo_size);
		ep_dbg(ep, "read udccsr:%03x, count:%d bytes%s req %p %d/%d\n",
			udc_ep_readl(ep, UDCCSR), count, is_short ? "/S" : "",
			&req->req, req->req.actual, req->req.length);

		/* completion */
		if (is_short || req->req.actual == req->req.length) {
			completed = 1;
			break;
		}
		/* finished that packet.  the next one may be waiting... */
	}
	return completed;
}