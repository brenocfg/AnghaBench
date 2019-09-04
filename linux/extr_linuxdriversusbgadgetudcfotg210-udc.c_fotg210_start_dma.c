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
typedef  int u32 ;
struct TYPE_6__ {int length; int actual; int /*<<< orphan*/ * buf; } ;
struct fotg210_request {TYPE_3__ req; } ;
struct TYPE_5__ {int maxpacket; } ;
struct fotg210_ep {scalar_t__ dir_in; TYPE_2__ ep; scalar_t__ epnum; TYPE_1__* fotg210; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int FIBCR_BCFX ; 
 scalar_t__ FOTG210_FIBCR (scalar_t__) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_disable_dma (struct fotg210_ep*) ; 
 int /*<<< orphan*/  fotg210_enable_dma (struct fotg210_ep*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fotg210_wait_dma_done (struct fotg210_ep*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void fotg210_start_dma(struct fotg210_ep *ep,
			struct fotg210_request *req)
{
	dma_addr_t d;
	u8 *buffer;
	u32 length;

	if (ep->epnum) {
		if (ep->dir_in) {
			buffer = req->req.buf;
			length = req->req.length;
		} else {
			buffer = req->req.buf + req->req.actual;
			length = ioread32(ep->fotg210->reg +
					FOTG210_FIBCR(ep->epnum - 1));
			length &= FIBCR_BCFX;
		}
	} else {
		buffer = req->req.buf + req->req.actual;
		if (req->req.length - req->req.actual > ep->ep.maxpacket)
			length = ep->ep.maxpacket;
		else
			length = req->req.length;
	}

	d = dma_map_single(NULL, buffer, length,
			ep->dir_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

	if (dma_mapping_error(NULL, d)) {
		pr_err("dma_mapping_error\n");
		return;
	}

	dma_sync_single_for_device(NULL, d, length,
				   ep->dir_in ? DMA_TO_DEVICE :
					DMA_FROM_DEVICE);

	fotg210_enable_dma(ep, d, length);

	/* check if dma is done */
	fotg210_wait_dma_done(ep);

	fotg210_disable_dma(ep);

	/* update actual transfer length */
	req->req.actual += length;

	dma_unmap_single(NULL, d, length, DMA_TO_DEVICE);
}