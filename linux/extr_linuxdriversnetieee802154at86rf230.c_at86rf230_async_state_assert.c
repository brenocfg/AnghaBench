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
typedef  scalar_t__ u8 ;
struct at86rf230_state_change {scalar_t__* buf; scalar_t__ const to_state; int /*<<< orphan*/  (* complete ) (void*) ;int /*<<< orphan*/  from_state; struct at86rf230_local* lp; } ;
struct at86rf230_local {scalar_t__ tx_retry; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AT86RF2XX_MAX_TX_RETRIES ; 
 scalar_t__ const STATE_BUSY_RX_AACK ; 
 scalar_t__ STATE_FORCE_TRX_OFF ; 
 scalar_t__ STATE_RX_AACK_ON ; 
 scalar_t__ STATE_TRX_OFF ; 
 scalar_t__ STATE_TX_ON ; 
 scalar_t__ const TRX_STATE_MASK ; 
 int /*<<< orphan*/  at86rf230_async_state_change (struct at86rf230_local*,struct at86rf230_state_change*,scalar_t__,int /*<<< orphan*/  (*) (void*)) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
at86rf230_async_state_assert(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;
	const u8 *buf = ctx->buf;
	const u8 trx_state = buf[1] & TRX_STATE_MASK;

	/* Assert state change */
	if (trx_state != ctx->to_state) {
		/* Special handling if transceiver state is in
		 * STATE_BUSY_RX_AACK and a SHR was detected.
		 */
		if  (trx_state == STATE_BUSY_RX_AACK) {
			/* Undocumented race condition. If we send a state
			 * change to STATE_RX_AACK_ON the transceiver could
			 * change his state automatically to STATE_BUSY_RX_AACK
			 * if a SHR was detected. This is not an error, but we
			 * can't assert this.
			 */
			if (ctx->to_state == STATE_RX_AACK_ON)
				goto done;

			/* If we change to STATE_TX_ON without forcing and
			 * transceiver state is STATE_BUSY_RX_AACK, we wait
			 * 'tFrame + tPAck' receiving time. In this time the
			 * PDU should be received. If the transceiver is still
			 * in STATE_BUSY_RX_AACK, we run a force state change
			 * to STATE_TX_ON. This is a timeout handling, if the
			 * transceiver stucks in STATE_BUSY_RX_AACK.
			 *
			 * Additional we do several retries to try to get into
			 * TX_ON state without forcing. If the retries are
			 * higher or equal than AT86RF2XX_MAX_TX_RETRIES we
			 * will do a force change.
			 */
			if (ctx->to_state == STATE_TX_ON ||
			    ctx->to_state == STATE_TRX_OFF) {
				u8 state = ctx->to_state;

				if (lp->tx_retry >= AT86RF2XX_MAX_TX_RETRIES)
					state = STATE_FORCE_TRX_OFF;
				lp->tx_retry++;

				at86rf230_async_state_change(lp, ctx, state,
							     ctx->complete);
				return;
			}
		}

		dev_warn(&lp->spi->dev, "unexcept state change from 0x%02x to 0x%02x. Actual state: 0x%02x\n",
			 ctx->from_state, ctx->to_state, trx_state);
	}

done:
	if (ctx->complete)
		ctx->complete(context);
}