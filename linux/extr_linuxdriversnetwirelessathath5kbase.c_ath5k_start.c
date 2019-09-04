#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath_common {int keymax; } ;
struct ath5k_hw {int imask; int ah_ack_bitrate_high; int /*<<< orphan*/  tx_complete_work; TYPE_3__* hw; int /*<<< orphan*/  status; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** bslot; int /*<<< orphan*/  curchan; int /*<<< orphan*/  opmode; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct TYPE_6__ {TYPE_2__ conf; } ;

/* Variables and functions */
 int AR5K_INT_FATAL ; 
 int AR5K_INT_GLOBAL ; 
 int AR5K_INT_MIB ; 
 int AR5K_INT_RXEOL ; 
 int AR5K_INT_RXERR ; 
 int AR5K_INT_RXOK ; 
 int AR5K_INT_RXORN ; 
 int AR5K_INT_TXDESC ; 
 int AR5K_INT_TXEOL ; 
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_RESET ; 
 int /*<<< orphan*/  ATH5K_TX_COMPLETE_POLL_INT ; 
 int /*<<< orphan*/  ATH_STAT_STARTED ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_modparam_no_hw_rfkill_switch ; 
 int ath5k_reset (struct ath5k_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath5k_rfkill_hw_start (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_stop_locked (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath_hw_keyreset (struct ath_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath5k_start(struct ieee80211_hw *hw)
{
	struct ath5k_hw *ah = hw->priv;
	struct ath_common *common = ath5k_hw_common(ah);
	int ret, i;

	mutex_lock(&ah->lock);

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "mode %d\n", ah->opmode);

	/*
	 * Stop anything previously setup.  This is safe
	 * no matter this is the first time through or not.
	 */
	ath5k_stop_locked(ah);

	/*
	 * The basic interface to setting the hardware in a good
	 * state is ``reset''.  On return the hardware is known to
	 * be powered up and with interrupts disabled.  This must
	 * be followed by initialization of the appropriate bits
	 * and then setup of the interrupt mask.
	 */
	ah->curchan = ah->hw->conf.chandef.chan;
	ah->imask = AR5K_INT_RXOK
		| AR5K_INT_RXERR
		| AR5K_INT_RXEOL
		| AR5K_INT_RXORN
		| AR5K_INT_TXDESC
		| AR5K_INT_TXEOL
		| AR5K_INT_FATAL
		| AR5K_INT_GLOBAL
		| AR5K_INT_MIB;

	ret = ath5k_reset(ah, NULL, false);
	if (ret)
		goto done;

	if (!ath5k_modparam_no_hw_rfkill_switch)
		ath5k_rfkill_hw_start(ah);

	/*
	 * Reset the key cache since some parts do not reset the
	 * contents on initial power up or resume from suspend.
	 */
	for (i = 0; i < common->keymax; i++)
		ath_hw_keyreset(common, (u16) i);

	/* Use higher rates for acks instead of base
	 * rate */
	ah->ah_ack_bitrate_high = true;

	for (i = 0; i < ARRAY_SIZE(ah->bslot); i++)
		ah->bslot[i] = NULL;

	ret = 0;
done:
	mmiowb();
	mutex_unlock(&ah->lock);

	set_bit(ATH_STAT_STARTED, ah->status);
	ieee80211_queue_delayed_work(ah->hw, &ah->tx_complete_work,
			msecs_to_jiffies(ATH5K_TX_COMPLETE_POLL_INT));

	return ret;
}