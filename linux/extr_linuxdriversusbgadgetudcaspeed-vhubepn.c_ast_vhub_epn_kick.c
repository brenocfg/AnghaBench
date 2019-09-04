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
struct TYPE_5__ {unsigned int actual; unsigned int length; int dma; scalar_t__ buf; int /*<<< orphan*/  zero; } ;
struct ast_vhub_req {int active; int last_desc; TYPE_2__ req; } ;
struct TYPE_6__ {scalar_t__ regs; scalar_t__ is_in; } ;
struct TYPE_4__ {unsigned int maxpacket; } ;
struct ast_vhub_ep {int buf_dma; TYPE_3__ epn; scalar_t__ buf; TYPE_1__ ep; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_EP_DESC_BASE ; 
 scalar_t__ AST_VHUB_EP_DESC_STATUS ; 
 int /*<<< orphan*/  EPVDBG (struct ast_vhub_ep*,char*,struct ast_vhub_req*,unsigned int,unsigned int,unsigned int,int) ; 
 int VHUB_EP_DMA_SET_TX_SIZE (unsigned int) ; 
 int VHUB_EP_DMA_SINGLE_KICK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  vhub_dma_workaround (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_epn_kick(struct ast_vhub_ep *ep, struct ast_vhub_req *req)
{
	unsigned int act = req->req.actual;
	unsigned int len = req->req.length;
	unsigned int chunk;

	/* There should be no DMA ongoing */
	WARN_ON(req->active);

	/* Calculate next chunk size */
	chunk = len - act;
	if (chunk > ep->ep.maxpacket)
		chunk = ep->ep.maxpacket;
	else if ((chunk < ep->ep.maxpacket) || !req->req.zero)
		req->last_desc = 1;

	EPVDBG(ep, "kick req %p act=%d/%d chunk=%d last=%d\n",
	       req, act, len, chunk, req->last_desc);

	/* If DMA unavailable, using staging EP buffer */
	if (!req->req.dma) {

		/* For IN transfers, copy data over first */
		if (ep->epn.is_in) {
			memcpy(ep->buf, req->req.buf + act, chunk);
			vhub_dma_workaround(ep->buf);
		}
		writel(ep->buf_dma, ep->epn.regs + AST_VHUB_EP_DESC_BASE);
	} else {
		if (ep->epn.is_in)
			vhub_dma_workaround(req->req.buf);
		writel(req->req.dma + act, ep->epn.regs + AST_VHUB_EP_DESC_BASE);
	}

	/* Start DMA */
	req->active = true;
	writel(VHUB_EP_DMA_SET_TX_SIZE(chunk),
	       ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
	writel(VHUB_EP_DMA_SET_TX_SIZE(chunk) | VHUB_EP_DMA_SINGLE_KICK,
	       ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
}