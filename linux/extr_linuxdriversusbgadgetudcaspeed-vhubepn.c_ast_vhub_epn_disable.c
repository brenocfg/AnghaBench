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
typedef  int /*<<< orphan*/  u32 ;
struct usb_ep {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * desc; } ;
struct TYPE_3__ {int enabled; int /*<<< orphan*/  g_idx; scalar_t__ regs; } ;
struct ast_vhub_ep {TYPE_2__ ep; TYPE_1__ epn; struct ast_vhub* vhub; } ;
struct ast_vhub {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_EP_ACK_IER ; 
 scalar_t__ AST_VHUB_EP_ACK_ISR ; 
 scalar_t__ AST_VHUB_EP_CONFIG ; 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*) ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  VHUB_EP_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_vhub_nuke (struct ast_vhub_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_vhub_stop_active_req (struct ast_vhub_ep*,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ast_vhub_ep* to_ast_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ast_vhub_epn_disable(struct usb_ep* u_ep)
{
	struct ast_vhub_ep *ep = to_ast_ep(u_ep);
	struct ast_vhub *vhub = ep->vhub;
	unsigned long flags;
	u32 imask, ep_ier;

	EPDBG(ep, "Disabling !\n");

	spin_lock_irqsave(&vhub->lock, flags);

	ep->epn.enabled = false;

	/* Stop active DMA if any */
	ast_vhub_stop_active_req(ep, false);

	/* Disable endpoint */
	writel(0, ep->epn.regs + AST_VHUB_EP_CONFIG);

	/* Disable ACK interrupt */
	imask = VHUB_EP_IRQ(ep->epn.g_idx);
	ep_ier = readl(vhub->regs + AST_VHUB_EP_ACK_IER);
	ep_ier &= ~imask;
	writel(ep_ier, vhub->regs + AST_VHUB_EP_ACK_IER);
	writel(imask, vhub->regs + AST_VHUB_EP_ACK_ISR);

	/* Nuke all pending requests */
	ast_vhub_nuke(ep, -ESHUTDOWN);

	/* No more descriptor associated with request */
	ep->ep.desc = NULL;

	spin_unlock_irqrestore(&vhub->lock, flags);

	return 0;
}