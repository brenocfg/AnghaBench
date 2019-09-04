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
struct hwbus_priv {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int irq_set_irq_wake (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cw1200_spi_pm(struct hwbus_priv *self, bool suspend)
{
	return irq_set_irq_wake(self->func->irq, suspend);
}