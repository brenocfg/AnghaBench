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
struct sk_buff {int dummy; } ;
struct ieee802154_hw {struct at86rf230_local* priv; } ;
struct at86rf230_state_change {int dummy; } ;
struct at86rf230_local {int is_tx_from_off; int /*<<< orphan*/  cal_timeout; scalar_t__ tx_retry; struct sk_buff* tx_skb; struct at86rf230_state_change tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_TRX_OFF ; 
 int /*<<< orphan*/  at86rf230_async_state_change (struct at86rf230_local*,struct at86rf230_state_change*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct at86rf230_state_change*)) ; 
 int /*<<< orphan*/  at86rf230_xmit_start (struct at86rf230_state_change*) ; 
 scalar_t__ time_is_before_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
at86rf230_xmit(struct ieee802154_hw *hw, struct sk_buff *skb)
{
	struct at86rf230_local *lp = hw->priv;
	struct at86rf230_state_change *ctx = &lp->tx;

	lp->tx_skb = skb;
	lp->tx_retry = 0;

	/* After 5 minutes in PLL and the same frequency we run again the
	 * calibration loops which is recommended by at86rf2xx datasheets.
	 *
	 * The calibration is initiate by a state change from TRX_OFF
	 * to TX_ON, the lp->cal_timeout should be reinit by state_delay
	 * function then to start in the next 5 minutes.
	 */
	if (time_is_before_jiffies(lp->cal_timeout)) {
		lp->is_tx_from_off = true;
		at86rf230_async_state_change(lp, ctx, STATE_TRX_OFF,
					     at86rf230_xmit_start);
	} else {
		lp->is_tx_from_off = false;
		at86rf230_xmit_start(ctx);
	}

	return 0;
}