#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct musb {int /*<<< orphan*/  xceiv; scalar_t__ dma_controller; int /*<<< orphan*/  controller; int /*<<< orphan*/  lock; int /*<<< orphan*/  mregs; int /*<<< orphan*/  deassert_reset_work; int /*<<< orphan*/  finish_resume_work; int /*<<< orphan*/  irq_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct musb* dev_to_musb (struct device*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_disable_interrupts (struct musb*) ; 
 int /*<<< orphan*/  musb_dma_controller_destroy (scalar_t__) ; 
 int /*<<< orphan*/  musb_exit_debugfs (struct musb*) ; 
 int /*<<< orphan*/  musb_free (struct musb*) ; 
 int /*<<< orphan*/  musb_gadget_cleanup (struct musb*) ; 
 int /*<<< orphan*/  musb_host_cleanup (struct musb*) ; 
 int /*<<< orphan*/ * musb_phy_callback ; 
 int /*<<< orphan*/  musb_platform_disable (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_exit (struct musb*) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int musb_remove(struct platform_device *pdev)
{
	struct device	*dev = &pdev->dev;
	struct musb	*musb = dev_to_musb(dev);
	unsigned long	flags;

	/* this gets called on rmmod.
	 *  - Host mode: host may still be active
	 *  - Peripheral mode: peripheral is deactivated (or never-activated)
	 *  - OTG mode: both roles are deactivated (or never-activated)
	 */
	musb_exit_debugfs(musb);

	cancel_delayed_work_sync(&musb->irq_work);
	cancel_delayed_work_sync(&musb->finish_resume_work);
	cancel_delayed_work_sync(&musb->deassert_reset_work);
	pm_runtime_get_sync(musb->controller);
	musb_host_cleanup(musb);
	musb_gadget_cleanup(musb);

	musb_platform_disable(musb);
	spin_lock_irqsave(&musb->lock, flags);
	musb_disable_interrupts(musb);
	musb_writeb(musb->mregs, MUSB_DEVCTL, 0);
	spin_unlock_irqrestore(&musb->lock, flags);
	musb_platform_exit(musb);

	pm_runtime_dont_use_autosuspend(musb->controller);
	pm_runtime_put_sync(musb->controller);
	pm_runtime_disable(musb->controller);
	musb_phy_callback = NULL;
	if (musb->dma_controller)
		musb_dma_controller_destroy(musb->dma_controller);
	usb_phy_shutdown(musb->xceiv);
	musb_free(musb);
	device_init_wakeup(dev, 0);
	return 0;
}