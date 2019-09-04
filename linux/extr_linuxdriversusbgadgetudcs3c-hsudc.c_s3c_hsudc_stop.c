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
struct usb_gadget {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct s3c_hsudc {int /*<<< orphan*/ * driver; int /*<<< orphan*/  supplies; int /*<<< orphan*/  irq; TYPE_3__* transceiver; int /*<<< orphan*/  lock; TYPE_2__* pd; int /*<<< orphan*/  dev; TYPE_1__ gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  otg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* gpio_uninit ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_3__*) ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_peripheral (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hsudc_stop_activity (struct s3c_hsudc*) ; 
 int /*<<< orphan*/  s3c_hsudc_uninit_phy () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 
 struct s3c_hsudc* to_hsudc (struct usb_gadget*) ; 

__attribute__((used)) static int s3c_hsudc_stop(struct usb_gadget *gadget)
{
	struct s3c_hsudc *hsudc = to_hsudc(gadget);
	unsigned long flags;

	if (!hsudc)
		return -ENODEV;

	spin_lock_irqsave(&hsudc->lock, flags);
	hsudc->gadget.speed = USB_SPEED_UNKNOWN;
	s3c_hsudc_uninit_phy();

	pm_runtime_put(hsudc->dev);

	if (hsudc->pd->gpio_uninit)
		hsudc->pd->gpio_uninit();
	s3c_hsudc_stop_activity(hsudc);
	spin_unlock_irqrestore(&hsudc->lock, flags);

	if (!IS_ERR_OR_NULL(hsudc->transceiver))
		(void) otg_set_peripheral(hsudc->transceiver->otg, NULL);

	disable_irq(hsudc->irq);

	regulator_bulk_disable(ARRAY_SIZE(hsudc->supplies), hsudc->supplies);
	hsudc->driver = NULL;

	return 0;
}