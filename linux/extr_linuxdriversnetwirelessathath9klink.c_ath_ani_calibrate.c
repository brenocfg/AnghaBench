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
typedef  unsigned int u32 ;
struct timer_list {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  paprd_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  ps_flags; struct ath_hw* sc_ah; } ;
struct TYPE_5__ {unsigned int ani_poll_interval; } ;
struct ath_hw {scalar_t__ opmode; scalar_t__ power_mode; scalar_t__ ani_skip_count; int /*<<< orphan*/  paprd_table_write_done; TYPE_3__* caldata; TYPE_1__ config; int /*<<< orphan*/  rxchainmask; int /*<<< orphan*/  curchan; } ;
struct TYPE_6__ {unsigned int longcal_timer; int caldone; unsigned int shortcal_timer; unsigned int resetcal_timer; unsigned int checkani_timer; int /*<<< orphan*/  timer; } ;
struct ath_common {TYPE_2__ ani; int /*<<< orphan*/  cc_lock; scalar_t__ priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  timer; } ;
struct TYPE_7__ {int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 scalar_t__ ATH9K_PM_AWAKE ; 
 scalar_t__ ATH_ANI_MAX_SKIP_COUNT ; 
 unsigned int ATH_AP_SHORT_CALINTERVAL ; 
 unsigned int ATH_LONG_CALINTERVAL ; 
 unsigned int ATH_LONG_CALINTERVAL_INT ; 
 unsigned int ATH_RESTART_CALINTERVAL ; 
 unsigned int ATH_STA_SHORT_CALINTERVAL ; 
 int /*<<< orphan*/  NFCAL_INTF ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  PAPRD_DONE ; 
 int /*<<< orphan*/  PS_WAIT_FOR_ANI ; 
 int /*<<< orphan*/  RESET_TYPE_CALIBRATION ; 
 TYPE_4__ ani ; 
 scalar_t__ ar9003_is_paprd_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_ani_monitor (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int ath9k_hw_calibrate (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ath9k_hw_reset_calvalid (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_queue_reset (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ath_paprd_activate (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_update_survey_stats (struct ath_softc*) ; 
 struct ath_common* common ; 
 struct ath_common* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 unsigned int jiffies_to_msecs (scalar_t__) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath_ani_calibrate(struct timer_list *t)
{
	struct ath_common *common = from_timer(common, t, ani.timer);
	struct ath_softc *sc = (struct ath_softc *)common->priv;
	struct ath_hw *ah = sc->sc_ah;
	bool longcal = false;
	bool shortcal = false;
	bool aniflag = false;
	unsigned int timestamp = jiffies_to_msecs(jiffies);
	u32 cal_interval, short_cal_interval, long_cal_interval;
	unsigned long flags;

	if (ah->caldata && test_bit(NFCAL_INTF, &ah->caldata->cal_flags))
		long_cal_interval = ATH_LONG_CALINTERVAL_INT;
	else
		long_cal_interval = ATH_LONG_CALINTERVAL;

	short_cal_interval = (ah->opmode == NL80211_IFTYPE_AP) ?
		ATH_AP_SHORT_CALINTERVAL : ATH_STA_SHORT_CALINTERVAL;

	/* Only calibrate if awake */
	if (sc->sc_ah->power_mode != ATH9K_PM_AWAKE) {
		if (++ah->ani_skip_count >= ATH_ANI_MAX_SKIP_COUNT) {
			spin_lock_irqsave(&sc->sc_pm_lock, flags);
			sc->ps_flags |= PS_WAIT_FOR_ANI;
			spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		}
		goto set_timer;
	}
	ah->ani_skip_count = 0;
	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	sc->ps_flags &= ~PS_WAIT_FOR_ANI;
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	ath9k_ps_wakeup(sc);

	/* Long calibration runs independently of short calibration. */
	if ((timestamp - common->ani.longcal_timer) >= long_cal_interval) {
		longcal = true;
		common->ani.longcal_timer = timestamp;
	}

	/* Short calibration applies only while caldone is false */
	if (!common->ani.caldone) {
		if ((timestamp - common->ani.shortcal_timer) >= short_cal_interval) {
			shortcal = true;
			common->ani.shortcal_timer = timestamp;
			common->ani.resetcal_timer = timestamp;
		}
	} else {
		if ((timestamp - common->ani.resetcal_timer) >=
		    ATH_RESTART_CALINTERVAL) {
			common->ani.caldone = ath9k_hw_reset_calvalid(ah);
			if (common->ani.caldone)
				common->ani.resetcal_timer = timestamp;
		}
	}

	/* Verify whether we must check ANI */
	if ((timestamp - common->ani.checkani_timer) >= ah->config.ani_poll_interval) {
		aniflag = true;
		common->ani.checkani_timer = timestamp;
	}

	/* Call ANI routine if necessary */
	if (aniflag) {
		spin_lock_irqsave(&common->cc_lock, flags);
		ath9k_hw_ani_monitor(ah, ah->curchan);
		ath_update_survey_stats(sc);
		spin_unlock_irqrestore(&common->cc_lock, flags);
	}

	/* Perform calibration if necessary */
	if (longcal || shortcal) {
		int ret = ath9k_hw_calibrate(ah, ah->curchan, ah->rxchainmask,
					     longcal);
		if (ret < 0) {
			common->ani.caldone = 0;
			ath9k_queue_reset(sc, RESET_TYPE_CALIBRATION);
			return;
		}

		common->ani.caldone = ret;
	}

	ath_dbg(common, ANI,
		"Calibration @%lu finished: %s %s %s, caldone: %s\n",
		jiffies,
		longcal ? "long" : "", shortcal ? "short" : "",
		aniflag ? "ani" : "", common->ani.caldone ? "true" : "false");

	ath9k_ps_restore(sc);

set_timer:
	/*
	* Set timer interval based on previous results.
	* The interval must be the shortest necessary to satisfy ANI,
	* short calibration and long calibration.
	*/
	cal_interval = ATH_LONG_CALINTERVAL;
	cal_interval = min(cal_interval, (u32)ah->config.ani_poll_interval);
	if (!common->ani.caldone)
		cal_interval = min(cal_interval, (u32)short_cal_interval);

	mod_timer(&common->ani.timer, jiffies + msecs_to_jiffies(cal_interval));

	if (ar9003_is_paprd_enabled(ah) && ah->caldata) {
		if (!test_bit(PAPRD_DONE, &ah->caldata->cal_flags)) {
			ieee80211_queue_work(sc->hw, &sc->paprd_work);
		} else if (!ah->paprd_table_write_done) {
			ath9k_ps_wakeup(sc);
			ath_paprd_activate(sc);
			ath9k_ps_restore(sc);
		}
	}
}