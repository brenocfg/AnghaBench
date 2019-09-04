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
struct TYPE_4__ {unsigned int length; scalar_t__ actual; struct nbu2ss_udc* context; int /*<<< orphan*/  status; int /*<<< orphan*/  complete; int /*<<< orphan*/  zero; scalar_t__ dma; void* buf; } ;
struct TYPE_3__ {TYPE_2__ req; } ;
struct nbu2ss_udc {TYPE_1__ ep0_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _nbu2ss_ep0_complete ; 

__attribute__((used)) static void _nbu2ss_create_ep0_packet(
	struct nbu2ss_udc *udc,
	void *p_buf,
	unsigned length
)
{
	udc->ep0_req.req.buf		= p_buf;
	udc->ep0_req.req.length		= length;
	udc->ep0_req.req.dma		= 0;
	udc->ep0_req.req.zero		= TRUE;
	udc->ep0_req.req.complete	= _nbu2ss_ep0_complete;
	udc->ep0_req.req.status		= -EINPROGRESS;
	udc->ep0_req.req.context	= udc;
	udc->ep0_req.req.actual		= 0;
}