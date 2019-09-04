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
typedef  int u32 ;
struct usb_ep {int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/ * name; } ;
struct s3c2410_ep {int halted; int num; int /*<<< orphan*/  dev; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_NORMAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  S3C2410_UDC_EP_INT_EN_REG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  s3c2410_udc_nuke (int /*<<< orphan*/ ,struct s3c2410_ep*,int /*<<< orphan*/ ) ; 
 struct s3c2410_ep* to_s3c2410_ep (struct usb_ep*) ; 
 int udc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2410_udc_ep_disable(struct usb_ep *_ep)
{
	struct s3c2410_ep *ep = to_s3c2410_ep(_ep);
	unsigned long flags;
	u32 int_en_reg;

	if (!_ep || !ep->ep.desc) {
		dprintk(DEBUG_NORMAL, "%s not enabled\n",
			_ep ? ep->ep.name : NULL);
		return -EINVAL;
	}

	local_irq_save(flags);

	dprintk(DEBUG_NORMAL, "ep_disable: %s\n", _ep->name);

	ep->ep.desc = NULL;
	ep->halted = 1;

	s3c2410_udc_nuke(ep->dev, ep, -ESHUTDOWN);

	/* disable irqs */
	int_en_reg = udc_read(S3C2410_UDC_EP_INT_EN_REG);
	udc_write(int_en_reg & ~(1<<ep->num), S3C2410_UDC_EP_INT_EN_REG);

	local_irq_restore(flags);

	dprintk(DEBUG_NORMAL, "%s disabled\n", _ep->name);

	return 0;
}