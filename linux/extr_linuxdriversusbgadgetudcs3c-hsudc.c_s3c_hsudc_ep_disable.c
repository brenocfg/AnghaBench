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
struct usb_ep {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; } ;
struct s3c_hsudc_ep {int stopped; TYPE_1__ ep; int /*<<< orphan*/  bEndpointAddress; struct s3c_hsudc* dev; } ;
struct s3c_hsudc {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 scalar_t__ S3C_EIER ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ep_index (struct s3c_hsudc_ep*) ; 
 struct s3c_hsudc_ep* our_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  s3c_hsudc_nuke_ep (struct s3c_hsudc_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_index (struct s3c_hsudc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s3c_hsudc_ep_disable(struct usb_ep *_ep)
{
	struct s3c_hsudc_ep *hsep = our_ep(_ep);
	struct s3c_hsudc *hsudc = hsep->dev;
	unsigned long flags;

	if (!_ep || !hsep->ep.desc)
		return -EINVAL;

	spin_lock_irqsave(&hsudc->lock, flags);

	set_index(hsudc, hsep->bEndpointAddress);
	__clear_bit(ep_index(hsep), hsudc->regs + S3C_EIER);

	s3c_hsudc_nuke_ep(hsep, -ESHUTDOWN);

	hsep->ep.desc = NULL;
	hsep->stopped = 1;

	spin_unlock_irqrestore(&hsudc->lock, flags);
	return 0;
}