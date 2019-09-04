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
struct cdc_ncm_ctx {int /*<<< orphan*/  timer_interval; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdc_ncm_tx_timeout_start(struct cdc_ncm_ctx *ctx)
{
	/* start timer, if not already started */
	if (!(hrtimer_active(&ctx->tx_timer) || atomic_read(&ctx->stop)))
		hrtimer_start(&ctx->tx_timer,
				ctx->timer_interval,
				HRTIMER_MODE_REL);
}