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
typedef  size_t u32 ;
struct udc {int /*<<< orphan*/  lock; TYPE_2__* regs; int /*<<< orphan*/ * ep; int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t AMD_ADDBITS (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  UDC_DEVCFG_SPD ; 
 int /*<<< orphan*/  UDC_DEVCFG_SPD_FS ; 
 size_t UDC_EP0IN_IX ; 
 size_t UDC_EP_NUM ; 
 int /*<<< orphan*/  empty_req_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soft_reset_occured ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_enable_dev_setup_interrupts (struct udc*) ; 
 int /*<<< orphan*/  udc_soft_reset (struct udc*) ; 
 scalar_t__ use_fullspeed ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_tasklet_disconnect(unsigned long par)
{
	struct udc *dev = (struct udc *)(*((struct udc **) par));
	u32 tmp;

	DBG(dev, "Tasklet disconnect\n");
	spin_lock_irq(&dev->lock);

	if (dev->driver) {
		spin_unlock(&dev->lock);
		dev->driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);

		/* empty queues */
		for (tmp = 0; tmp < UDC_EP_NUM; tmp++)
			empty_req_queue(&dev->ep[tmp]);

	}

	/* disable ep0 */
	ep_init(dev->regs,
			&dev->ep[UDC_EP0IN_IX]);


	if (!soft_reset_occured) {
		/* init controller by soft reset */
		udc_soft_reset(dev);
		soft_reset_occured++;
	}

	/* re-enable dev interrupts */
	udc_enable_dev_setup_interrupts(dev);
	/* back to full speed ? */
	if (use_fullspeed) {
		tmp = readl(&dev->regs->cfg);
		tmp = AMD_ADDBITS(tmp, UDC_DEVCFG_SPD_FS, UDC_DEVCFG_SPD);
		writel(tmp, &dev->regs->cfg);
	}

	spin_unlock_irq(&dev->lock);
}