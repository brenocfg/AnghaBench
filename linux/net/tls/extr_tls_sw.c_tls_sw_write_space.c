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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct tls_sw_context_tx {TYPE_1__ tx_work; int /*<<< orphan*/  tx_bitmask; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_TX_SCHEDULED ; 
 scalar_t__ is_tx_ready (struct tls_sw_context_tx*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

void tls_sw_write_space(struct sock *sk, struct tls_context *ctx)
{
	struct tls_sw_context_tx *tx_ctx = tls_sw_ctx_tx(ctx);

	/* Schedule the transmission if tx list is ready */
	if (is_tx_ready(tx_ctx) &&
	    !test_and_set_bit(BIT_TX_SCHEDULED, &tx_ctx->tx_bitmask))
		schedule_delayed_work(&tx_ctx->tx_work.work, 0);
}