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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {unsigned int length; unsigned int actual; int /*<<< orphan*/  zero; int /*<<< orphan*/  status; int /*<<< orphan*/ * buf; } ;
struct udc_request {TYPE_2__ req; } ;
struct TYPE_6__ {unsigned int maxpacket; int /*<<< orphan*/  name; } ;
struct udc_ep {int /*<<< orphan*/  dev; TYPE_3__ ep; TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  sts; } ;

/* Variables and functions */
 unsigned int AMD_GETBITS (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  UDC_EPSTS_RX_PKT_SIZE ; 
 int /*<<< orphan*/  VDBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_rxfifo_read_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
udc_rxfifo_read(struct udc_ep *ep, struct udc_request *req)
{
	u8 *buf;
	unsigned buf_space;
	unsigned bytes = 0;
	unsigned finished = 0;

	/* received number bytes */
	bytes = readl(&ep->regs->sts);
	bytes = AMD_GETBITS(bytes, UDC_EPSTS_RX_PKT_SIZE);

	buf_space = req->req.length - req->req.actual;
	buf = req->req.buf + req->req.actual;
	if (bytes > buf_space) {
		if ((buf_space % ep->ep.maxpacket) != 0) {
			DBG(ep->dev,
				"%s: rx %d bytes, rx-buf space = %d bytesn\n",
				ep->ep.name, bytes, buf_space);
			req->req.status = -EOVERFLOW;
		}
		bytes = buf_space;
	}
	req->req.actual += bytes;

	/* last packet ? */
	if (((bytes % ep->ep.maxpacket) != 0) || (!bytes)
		|| ((req->req.actual == req->req.length) && !req->req.zero))
		finished = 1;

	/* read rx fifo bytes */
	VDBG(ep->dev, "ep %s: rxfifo read %d bytes\n", ep->ep.name, bytes);
	udc_rxfifo_read_bytes(ep->dev, buf, bytes);

	return finished;
}