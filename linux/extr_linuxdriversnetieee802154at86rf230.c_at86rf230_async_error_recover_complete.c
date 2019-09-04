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
struct at86rf230_state_change {scalar_t__ free; struct at86rf230_local* lp; } ;
struct at86rf230_local {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee802154_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct at86rf230_state_change*) ; 

__attribute__((used)) static void
at86rf230_async_error_recover_complete(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;

	if (ctx->free)
		kfree(ctx);

	ieee802154_wake_queue(lp->hw);
}