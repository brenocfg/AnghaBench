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
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct at86rf230_state_change {int free; int* buf; TYPE_1__ msg; } ;
struct at86rf230_local {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CMD_REG ; 
 int CMD_REG_MASK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RG_IRQ_STATUS ; 
 int /*<<< orphan*/  at86rf230_async_error (struct at86rf230_local*,struct at86rf230_state_change*,int) ; 
 int /*<<< orphan*/  at86rf230_irq_status ; 
 int /*<<< orphan*/  at86rf230_setup_spi_messages (struct at86rf230_local*,struct at86rf230_state_change*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 struct at86rf230_state_change* kzalloc (int,int /*<<< orphan*/ ) ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t at86rf230_isr(int irq, void *data)
{
	struct at86rf230_local *lp = data;
	struct at86rf230_state_change *ctx;
	int rc;

	disable_irq_nosync(irq);

	ctx = kzalloc(sizeof(*ctx), GFP_ATOMIC);
	if (!ctx) {
		enable_irq(irq);
		return IRQ_NONE;
	}

	at86rf230_setup_spi_messages(lp, ctx);
	/* tell on error handling to free ctx */
	ctx->free = true;

	ctx->buf[0] = (RG_IRQ_STATUS & CMD_REG_MASK) | CMD_REG;
	ctx->msg.complete = at86rf230_irq_status;
	rc = spi_async(lp->spi, &ctx->msg);
	if (rc) {
		at86rf230_async_error(lp, ctx, rc);
		enable_irq(irq);
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}