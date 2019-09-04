#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct s3c_hsudc_ep {int stopped; } ;
struct TYPE_7__ {scalar_t__ speed; } ;
struct s3c_hsudc {int /*<<< orphan*/  lock; scalar_t__ regs; struct s3c_hsudc_ep* ep; int /*<<< orphan*/  ep0state; TYPE_2__* pd; TYPE_3__ gadget; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int epnum; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;int /*<<< orphan*/  (* suspend ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ S3C_EIR ; 
 int S3C_EIR_EP0 ; 
 scalar_t__ S3C_SSR ; 
 int S3C_SSR_DTZIEN_EN ; 
 int S3C_SSR_ERR ; 
 int S3C_SSR_HSP ; 
 int S3C_SSR_RESET ; 
 int S3C_SSR_RESUME ; 
 int S3C_SSR_SDE ; 
 int S3C_SSR_SUSPEND ; 
 int S3C_SSR_VBUSON ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 scalar_t__ ep_is_in (struct s3c_hsudc_ep*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c_hsudc_epin_intr (struct s3c_hsudc*,int) ; 
 int /*<<< orphan*/  s3c_hsudc_epout_intr (struct s3c_hsudc*,int) ; 
 int /*<<< orphan*/  s3c_hsudc_handle_ep0_intr (struct s3c_hsudc*) ; 
 int /*<<< orphan*/  s3c_hsudc_nuke_ep (struct s3c_hsudc_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hsudc_reconfig (struct s3c_hsudc*) ; 
 int /*<<< orphan*/  set_index (struct s3c_hsudc*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t s3c_hsudc_irq(int irq, void *_dev)
{
	struct s3c_hsudc *hsudc = _dev;
	struct s3c_hsudc_ep *hsep;
	u32 ep_intr;
	u32 sys_status;
	u32 ep_idx;

	spin_lock(&hsudc->lock);

	sys_status = readl(hsudc->regs + S3C_SSR);
	ep_intr = readl(hsudc->regs + S3C_EIR) & 0x3FF;

	if (!ep_intr && !(sys_status & S3C_SSR_DTZIEN_EN)) {
		spin_unlock(&hsudc->lock);
		return IRQ_HANDLED;
	}

	if (sys_status) {
		if (sys_status & S3C_SSR_VBUSON)
			writel(S3C_SSR_VBUSON, hsudc->regs + S3C_SSR);

		if (sys_status & S3C_SSR_ERR)
			writel(S3C_SSR_ERR, hsudc->regs + S3C_SSR);

		if (sys_status & S3C_SSR_SDE) {
			writel(S3C_SSR_SDE, hsudc->regs + S3C_SSR);
			hsudc->gadget.speed = (sys_status & S3C_SSR_HSP) ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
		}

		if (sys_status & S3C_SSR_SUSPEND) {
			writel(S3C_SSR_SUSPEND, hsudc->regs + S3C_SSR);
			if (hsudc->gadget.speed != USB_SPEED_UNKNOWN
				&& hsudc->driver && hsudc->driver->suspend)
				hsudc->driver->suspend(&hsudc->gadget);
		}

		if (sys_status & S3C_SSR_RESUME) {
			writel(S3C_SSR_RESUME, hsudc->regs + S3C_SSR);
			if (hsudc->gadget.speed != USB_SPEED_UNKNOWN
				&& hsudc->driver && hsudc->driver->resume)
				hsudc->driver->resume(&hsudc->gadget);
		}

		if (sys_status & S3C_SSR_RESET) {
			writel(S3C_SSR_RESET, hsudc->regs + S3C_SSR);
			for (ep_idx = 0; ep_idx < hsudc->pd->epnum; ep_idx++) {
				hsep = &hsudc->ep[ep_idx];
				hsep->stopped = 1;
				s3c_hsudc_nuke_ep(hsep, -ECONNRESET);
			}
			s3c_hsudc_reconfig(hsudc);
			hsudc->ep0state = WAIT_FOR_SETUP;
		}
	}

	if (ep_intr & S3C_EIR_EP0) {
		writel(S3C_EIR_EP0, hsudc->regs + S3C_EIR);
		set_index(hsudc, 0);
		s3c_hsudc_handle_ep0_intr(hsudc);
	}

	ep_intr >>= 1;
	ep_idx = 1;
	while (ep_intr) {
		if (ep_intr & 1)  {
			hsep = &hsudc->ep[ep_idx];
			set_index(hsudc, ep_idx);
			writel(1 << ep_idx, hsudc->regs + S3C_EIR);
			if (ep_is_in(hsep))
				s3c_hsudc_epin_intr(hsudc, ep_idx);
			else
				s3c_hsudc_epout_intr(hsudc, ep_idx);
		}
		ep_intr >>= 1;
		ep_idx++;
	}

	spin_unlock(&hsudc->lock);
	return IRQ_HANDLED;
}