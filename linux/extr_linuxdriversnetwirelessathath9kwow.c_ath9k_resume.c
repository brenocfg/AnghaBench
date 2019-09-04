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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_pcu_lock; int /*<<< orphan*/  wow_intr_before_sleep; struct ath_hw* sc_ah; } ;
struct ath_hw {int /*<<< orphan*/  imask; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_WOW_ENABLED ; 
 int /*<<< orphan*/  WOW ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_disable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_enable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wow_wakeup (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_start_btcoex (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_restart_work (struct ath_softc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ath9k_resume(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	u8 status;

	mutex_lock(&sc->mutex);

	ath9k_ps_wakeup(sc);

	spin_lock_bh(&sc->sc_pcu_lock);

	ath9k_hw_disable_interrupts(ah);
	ah->imask = sc->wow_intr_before_sleep;
	ath9k_hw_set_interrupts(ah);
	ath9k_hw_enable_interrupts(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	status = ath9k_hw_wow_wakeup(ah);
	ath_dbg(common, WOW, "Resume with WoW status: 0x%x\n", status);

	ath_restart_work(sc);
	ath9k_start_btcoex(sc);

	clear_bit(ATH_OP_WOW_ENABLED, &common->op_flags);

	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);

	return 0;
}