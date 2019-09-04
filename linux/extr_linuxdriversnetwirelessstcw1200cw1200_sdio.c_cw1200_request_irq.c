#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hwbus_priv {TYPE_1__* pdata; TYPE_2__* func; } ;
struct TYPE_5__ {int /*<<< orphan*/  num; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  SDIO_CCCR_IENx ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cw1200_gpio_hardirq ; 
 int /*<<< orphan*/  cw1200_gpio_irq ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct hwbus_priv*) ; 
 int /*<<< orphan*/  sdio_f0_readb (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_f0_writeb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int cw1200_request_irq(struct hwbus_priv *self)
{
	int ret;
	u8 cccr;

	cccr = sdio_f0_readb(self->func, SDIO_CCCR_IENx, &ret);
	if (WARN_ON(ret))
		goto err;

	/* Master interrupt enable ... */
	cccr |= BIT(0);

	/* ... for our function */
	cccr |= BIT(self->func->num);

	sdio_f0_writeb(self->func, cccr, SDIO_CCCR_IENx, &ret);
	if (WARN_ON(ret))
		goto err;

	ret = enable_irq_wake(self->pdata->irq);
	if (WARN_ON(ret))
		goto err;

	/* Request the IRQ */
	ret =  request_threaded_irq(self->pdata->irq, cw1200_gpio_hardirq,
				    cw1200_gpio_irq,
				    IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
				    "cw1200_wlan_irq", self);
	if (WARN_ON(ret))
		goto err;

	return 0;

err:
	return ret;
}