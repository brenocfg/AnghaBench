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
struct pxa_ep {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct pxa27x_request {int in_use; int /*<<< orphan*/  queue; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCSR ; 
 int /*<<< orphan*/  ep_vdbg (struct pxa_ep*,char*,struct pxa27x_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pio_irq_enable (struct pxa_ep*) ; 
 int /*<<< orphan*/  udc_ep_readl (struct pxa_ep*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ep_add_request(struct pxa_ep *ep, struct pxa27x_request *req)
{
	if (unlikely(!req))
		return;
	ep_vdbg(ep, "req:%p, lg=%d, udccsr=0x%03x\n", req,
		req->req.length, udc_ep_readl(ep, UDCCSR));

	req->in_use = 1;
	list_add_tail(&req->queue, &ep->queue);
	pio_irq_enable(ep);
}