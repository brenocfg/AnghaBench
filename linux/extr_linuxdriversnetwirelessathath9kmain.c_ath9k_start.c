#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  chandef; } ;
struct ieee80211_hw {TYPE_1__ conf; struct ath_softc* priv; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_pcu_lock; struct ath_hw* sc_ah; int /*<<< orphan*/  cur_chandef; struct ath_chanctx* cur_chan; } ;
struct TYPE_7__ {int hw_hang_checks; scalar_t__ led_active_high; } ;
struct TYPE_6__ {int hw_caps; } ;
struct ath_hw {int reset_power_on; int imask; int is_monitoring; scalar_t__ led_pin; TYPE_3__ config; TYPE_2__ caps; int /*<<< orphan*/  caldata; int /*<<< orphan*/  intr_ref_cnt; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct TYPE_8__ {struct ieee80211_channel* chan; } ;
struct ath_chanctx {TYPE_4__ chandef; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX_AS_OUTPUT ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int ATH9K_HW_CAP_EDMA ; 
 int ATH9K_HW_CAP_HT ; 
 int ATH9K_INT_BB_WATCHDOG ; 
 int ATH9K_INT_CST ; 
 int ATH9K_INT_FATAL ; 
 int ATH9K_INT_GLOBAL ; 
 int ATH9K_INT_GTT ; 
 int ATH9K_INT_RX ; 
 int ATH9K_INT_RXEOL ; 
 int ATH9K_INT_RXHP ; 
 int ATH9K_INT_RXLP ; 
 int ATH9K_INT_RXORN ; 
 int ATH9K_INT_TX ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int /*<<< orphan*/  CONFIG ; 
 int HW_BB_WATCHDOG ; 
 struct ath9k_channel* ath9k_cmn_get_channel (struct ieee80211_hw*,struct ath_hw*,TYPE_4__*) ; 
 int /*<<< orphan*/  ath9k_cmn_init_crypto (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_configpcipowersave (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_request_out (struct ath_hw*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ath9k_hw_reset (struct ath_hw*,struct ath9k_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_reset_tsf (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_gpio (struct ath_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_rng_start (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_complete_reset (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_mci_enable (struct ath_softc*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_start(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ieee80211_channel *curchan = sc->cur_chan->chandef.chan;
	struct ath_chanctx *ctx = sc->cur_chan;
	struct ath9k_channel *init_channel;
	int r;

	ath_dbg(common, CONFIG,
		"Starting driver with initial channel: %d MHz\n",
		curchan->center_freq);

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	init_channel = ath9k_cmn_get_channel(hw, ah, &ctx->chandef);
	sc->cur_chandef = hw->conf.chandef;

	/* Reset SERDES registers */
	ath9k_hw_configpcipowersave(ah, false);

	/*
	 * The basic interface to setting the hardware in a good
	 * state is ``reset''.  On return the hardware is known to
	 * be powered up and with interrupts disabled.  This must
	 * be followed by initialization of the appropriate bits
	 * and then setup of the interrupt mask.
	 */
	spin_lock_bh(&sc->sc_pcu_lock);

	atomic_set(&ah->intr_ref_cnt, -1);

	r = ath9k_hw_reset(ah, init_channel, ah->caldata, false);
	if (r) {
		ath_err(common,
			"Unable to reset hardware; reset status %d (freq %u MHz)\n",
			r, curchan->center_freq);
		ah->reset_power_on = false;
	}

	/* Setup our intr mask. */
	ah->imask = ATH9K_INT_TX | ATH9K_INT_RXEOL |
		    ATH9K_INT_RXORN | ATH9K_INT_FATAL |
		    ATH9K_INT_GLOBAL;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ah->imask |= ATH9K_INT_RXHP |
			     ATH9K_INT_RXLP;
	else
		ah->imask |= ATH9K_INT_RX;

	if (ah->config.hw_hang_checks & HW_BB_WATCHDOG)
		ah->imask |= ATH9K_INT_BB_WATCHDOG;

	/*
	 * Enable GTT interrupts only for AR9003/AR9004 chips
	 * for now.
	 */
	if (AR_SREV_9300_20_OR_LATER(ah))
		ah->imask |= ATH9K_INT_GTT;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_HT)
		ah->imask |= ATH9K_INT_CST;

	ath_mci_enable(sc);

	clear_bit(ATH_OP_INVALID, &common->op_flags);
	sc->sc_ah->is_monitoring = false;

	if (!ath_complete_reset(sc, false))
		ah->reset_power_on = false;

	if (ah->led_pin >= 0) {
		ath9k_hw_set_gpio(ah, ah->led_pin,
				  (ah->config.led_active_high) ? 1 : 0);
		ath9k_hw_gpio_request_out(ah, ah->led_pin, NULL,
					  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);
	}

	/*
	 * Reset key cache to sane defaults (all entries cleared) instead of
	 * semi-random values after suspend/resume.
	 */
	ath9k_cmn_init_crypto(sc->sc_ah);

	ath9k_hw_reset_tsf(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	ath9k_rng_start(sc);

	mutex_unlock(&sc->mutex);

	ath9k_ps_restore(sc);

	return 0;
}