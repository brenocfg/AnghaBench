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
struct hwbus_priv {scalar_t__ core; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  cw1200_irq_handler (scalar_t__) ; 
 int /*<<< orphan*/  cw1200_sdio_lock (struct hwbus_priv*) ; 
 int /*<<< orphan*/  cw1200_sdio_unlock (struct hwbus_priv*) ; 

__attribute__((used)) static irqreturn_t cw1200_gpio_irq(int irq, void *dev_id)
{
	struct hwbus_priv *self = dev_id;

	if (self->core) {
		cw1200_sdio_lock(self);
		cw1200_irq_handler(self->core);
		cw1200_sdio_unlock(self);
		return IRQ_HANDLED;
	} else {
		return IRQ_NONE;
	}
}