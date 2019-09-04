#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  function; } ;
struct TYPE_7__ {struct at86rf230_state_change* context; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct at86rf230_state_change {TYPE_5__ timer; TYPE_2__ msg; TYPE_3__ trx; int /*<<< orphan*/  buf; int /*<<< orphan*/  irq; struct at86rf230_local* lp; } ;
struct at86rf230_local {TYPE_1__* spi; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  at86rf230_async_state_timer ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  spi_message_init (TYPE_2__*) ; 

__attribute__((used)) static void
at86rf230_setup_spi_messages(struct at86rf230_local *lp,
			     struct at86rf230_state_change *state)
{
	state->lp = lp;
	state->irq = lp->spi->irq;
	spi_message_init(&state->msg);
	state->msg.context = state;
	state->trx.len = 2;
	state->trx.tx_buf = state->buf;
	state->trx.rx_buf = state->buf;
	spi_message_add_tail(&state->trx, &state->msg);
	hrtimer_init(&state->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	state->timer.function = at86rf230_async_state_timer;
}