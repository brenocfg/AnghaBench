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
typedef  int u8 ;
struct TYPE_2__ {void (* complete ) (void*) ;} ;
struct at86rf230_state_change {int* buf; TYPE_1__ msg; } ;
struct at86rf230_local {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int CMD_REG ; 
 int CMD_REG_MASK ; 
 int /*<<< orphan*/  at86rf230_async_error (struct at86rf230_local*,struct at86rf230_state_change*,int) ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
at86rf230_async_read_reg(struct at86rf230_local *lp, u8 reg,
			 struct at86rf230_state_change *ctx,
			 void (*complete)(void *context))
{
	int rc;

	u8 *tx_buf = ctx->buf;

	tx_buf[0] = (reg & CMD_REG_MASK) | CMD_REG;
	ctx->msg.complete = complete;
	rc = spi_async(lp->spi, &ctx->msg);
	if (rc)
		at86rf230_async_error(lp, ctx, rc);
}