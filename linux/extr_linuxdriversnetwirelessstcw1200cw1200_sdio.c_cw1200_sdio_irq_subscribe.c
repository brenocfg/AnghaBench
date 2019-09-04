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
 int cw1200_request_irq (struct hwbus_priv*) ; 
 int /*<<< orphan*/  cw1200_sdio_irq_handler ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_claim_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cw1200_sdio_irq_subscribe(struct hwbus_priv *self)
{
	int ret = 0;

	pr_debug("SW IRQ subscribe\n");
	sdio_claim_host(self->func);
	if (self->pdata->irq)
		ret = cw1200_request_irq(self);
	else
		ret = sdio_claim_irq(self->func, cw1200_sdio_irq_handler);

	sdio_release_host(self->func);
	return ret;
}