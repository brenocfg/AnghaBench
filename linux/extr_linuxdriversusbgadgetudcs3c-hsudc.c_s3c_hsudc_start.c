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
struct usb_gadget_driver {scalar_t__ max_speed; int /*<<< orphan*/  setup; } ;
struct usb_gadget {int dummy; } ;
struct TYPE_5__ {int name; } ;
struct s3c_hsudc {struct usb_gadget_driver* driver; int /*<<< orphan*/  supplies; TYPE_1__* pd; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; TYPE_2__ gadget; TYPE_3__* transceiver; } ;
struct TYPE_6__ {int /*<<< orphan*/  otg; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* gpio_init ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_3__*) ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int otg_set_peripheral (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hsudc_init_phy () ; 
 int /*<<< orphan*/  s3c_hsudc_reconfig (struct s3c_hsudc*) ; 
 int /*<<< orphan*/  stub1 () ; 
 struct s3c_hsudc* to_hsudc (struct usb_gadget*) ; 

__attribute__((used)) static int s3c_hsudc_start(struct usb_gadget *gadget,
		struct usb_gadget_driver *driver)
{
	struct s3c_hsudc *hsudc = to_hsudc(gadget);
	int ret;

	if (!driver
		|| driver->max_speed < USB_SPEED_FULL
		|| !driver->setup)
		return -EINVAL;

	if (!hsudc)
		return -ENODEV;

	if (hsudc->driver)
		return -EBUSY;

	hsudc->driver = driver;

	ret = regulator_bulk_enable(ARRAY_SIZE(hsudc->supplies),
				    hsudc->supplies);
	if (ret != 0) {
		dev_err(hsudc->dev, "failed to enable supplies: %d\n", ret);
		goto err_supplies;
	}

	/* connect to bus through transceiver */
	if (!IS_ERR_OR_NULL(hsudc->transceiver)) {
		ret = otg_set_peripheral(hsudc->transceiver->otg,
					&hsudc->gadget);
		if (ret) {
			dev_err(hsudc->dev, "%s: can't bind to transceiver\n",
					hsudc->gadget.name);
			goto err_otg;
		}
	}

	enable_irq(hsudc->irq);
	s3c_hsudc_reconfig(hsudc);

	pm_runtime_get_sync(hsudc->dev);

	s3c_hsudc_init_phy();
	if (hsudc->pd->gpio_init)
		hsudc->pd->gpio_init();

	return 0;
err_otg:
	regulator_bulk_disable(ARRAY_SIZE(hsudc->supplies), hsudc->supplies);
err_supplies:
	hsudc->driver = NULL;
	return ret;
}