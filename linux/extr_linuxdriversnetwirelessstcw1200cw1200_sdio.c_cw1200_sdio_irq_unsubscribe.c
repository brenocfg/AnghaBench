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
struct hwbus_priv {int /*<<< orphan*/  func; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_wake (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct hwbus_priv*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int sdio_release_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cw1200_sdio_irq_unsubscribe(struct hwbus_priv *self)
{
	int ret = 0;

	pr_debug("SW IRQ unsubscribe\n");

	if (self->pdata->irq) {
		disable_irq_wake(self->pdata->irq);
		free_irq(self->pdata->irq, self);
	} else {
		sdio_claim_host(self->func);
		ret = sdio_release_irq(self->func);
		sdio_release_host(self->func);
	}
	return ret;
}