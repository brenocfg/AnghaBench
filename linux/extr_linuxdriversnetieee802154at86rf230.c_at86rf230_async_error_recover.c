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
struct at86rf230_state_change {struct at86rf230_local* lp; } ;
struct at86rf230_local {scalar_t__ is_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_RX_AACK_ON ; 
 int /*<<< orphan*/  at86rf230_async_error_recover_complete ; 
 int /*<<< orphan*/  at86rf230_async_state_change (struct at86rf230_local*,struct at86rf230_state_change*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
at86rf230_async_error_recover(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;

	lp->is_tx = 0;
	at86rf230_async_state_change(lp, ctx, STATE_RX_AACK_ON,
				     at86rf230_async_error_recover_complete);
}