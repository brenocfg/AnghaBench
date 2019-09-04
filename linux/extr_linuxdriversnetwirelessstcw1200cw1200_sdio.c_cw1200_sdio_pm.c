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
struct hwbus_priv {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int irq_set_irq_wake (scalar_t__,int) ; 

__attribute__((used)) static int cw1200_sdio_pm(struct hwbus_priv *self, bool suspend)
{
	int ret = 0;

	if (self->pdata->irq)
		ret = irq_set_irq_wake(self->pdata->irq, suspend);
	return ret;
}