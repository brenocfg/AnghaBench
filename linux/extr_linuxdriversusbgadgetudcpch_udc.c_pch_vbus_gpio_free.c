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
struct TYPE_2__ {scalar_t__ port; scalar_t__ intr; } ;
struct pch_udc_dev {TYPE_1__ vbus_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct pch_udc_dev*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 

__attribute__((used)) static void pch_vbus_gpio_free(struct pch_udc_dev *dev)
{
	if (dev->vbus_gpio.intr)
		free_irq(dev->vbus_gpio.intr, dev);

	if (dev->vbus_gpio.port)
		gpio_free(dev->vbus_gpio.port);
}