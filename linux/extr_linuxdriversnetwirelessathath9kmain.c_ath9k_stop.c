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
struct ieee80211_hw {struct ath_softc* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/ * frag; } ;
struct ath_softc {int ps_idle; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_pcu_lock; TYPE_3__* cur_chan; TYPE_2__ rx; int /*<<< orphan*/  bcon_tasklet; int /*<<< orphan*/  intr_tq; int /*<<< orphan*/  irq; struct ath_hw* sc_ah; } ;
struct TYPE_4__ {scalar_t__ led_active_high; } ;
struct ath_hw {scalar_t__ led_pin; int /*<<< orphan*/  caldata; scalar_t__ curchan; TYPE_1__ config; int /*<<< orphan*/  imask; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  chandef; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY ; 
 int /*<<< orphan*/  ATH9K_INT_GLOBAL ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int /*<<< orphan*/  CONFIG ; 
 scalar_t__ ath9k_cmn_get_channel (struct ieee80211_hw*,struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_deinit_channel_context (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_configpcipowersave (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_disable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_request_in (struct ath_hw*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_hw_phy_disable (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_reset (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_gpio (struct ath_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_rng_stop (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_cancel_work (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_prepare_reset (struct ath_softc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_stop(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	bool prev_idle;

	ath9k_deinit_channel_context(sc);

	mutex_lock(&sc->mutex);

	ath9k_rng_stop(sc);

	ath_cancel_work(sc);

	if (test_bit(ATH_OP_INVALID, &common->op_flags)) {
		ath_dbg(common, ANY, "Device not present\n");
		mutex_unlock(&sc->mutex);
		return;
	}

	/* Ensure HW is awake when we try to shut it down. */
	ath9k_ps_wakeup(sc);

	spin_lock_bh(&sc->sc_pcu_lock);

	/* prevent tasklets to enable interrupts once we disable them */
	ah->imask &= ~ATH9K_INT_GLOBAL;

	/* make sure h/w will not generate any interrupt
	 * before setting the invalid flag. */
	ath9k_hw_disable_interrupts(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	/* we can now sync irq and kill any running tasklets, since we already
	 * disabled interrupts and not holding a spin lock */
	synchronize_irq(sc->irq);
	tasklet_kill(&sc->intr_tq);
	tasklet_kill(&sc->bcon_tasklet);

	prev_idle = sc->ps_idle;
	sc->ps_idle = true;

	spin_lock_bh(&sc->sc_pcu_lock);

	if (ah->led_pin >= 0) {
		ath9k_hw_set_gpio(ah, ah->led_pin,
				  (ah->config.led_active_high) ? 0 : 1);
		ath9k_hw_gpio_request_in(ah, ah->led_pin, NULL);
	}

	ath_prepare_reset(sc);

	if (sc->rx.frag) {
		dev_kfree_skb_any(sc->rx.frag);
		sc->rx.frag = NULL;
	}

	if (!ah->curchan)
		ah->curchan = ath9k_cmn_get_channel(hw, ah,
						    &sc->cur_chan->chandef);

	ath9k_hw_reset(ah, ah->curchan, ah->caldata, false);

	set_bit(ATH_OP_INVALID, &common->op_flags);

	ath9k_hw_phy_disable(ah);

	ath9k_hw_configpcipowersave(ah, true);

	spin_unlock_bh(&sc->sc_pcu_lock);

	ath9k_ps_restore(sc);

	sc->ps_idle = prev_idle;

	mutex_unlock(&sc->mutex);

	ath_dbg(common, CONFIG, "Driver halt\n");
}