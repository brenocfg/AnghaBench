#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {int ps_usecount; int /*<<< orphan*/  sc_pm_lock; TYPE_1__* sc_ah; int /*<<< orphan*/  sleep_timer; } ;
struct ath_common {int /*<<< orphan*/  cc_lock; int /*<<< orphan*/  cc_ani; int /*<<< orphan*/  cc_survey; } ;
typedef  enum ath9k_power_mode { ____Placeholder_ath9k_power_mode } ath9k_power_mode ;
struct TYPE_3__ {int power_mode; } ;

/* Variables and functions */
 int ATH9K_PM_AWAKE ; 
 struct ath_common* ath9k_hw_common (TYPE_1__*) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ath_hw_cycle_counters_update (struct ath_common*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ath9k_ps_wakeup(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned long flags;
	enum ath9k_power_mode power_mode;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	if (++sc->ps_usecount != 1)
		goto unlock;

	del_timer_sync(&sc->sleep_timer);
	power_mode = sc->sc_ah->power_mode;
	ath9k_hw_setpower(sc->sc_ah, ATH9K_PM_AWAKE);

	/*
	 * While the hardware is asleep, the cycle counters contain no
	 * useful data. Better clear them now so that they don't mess up
	 * survey data results.
	 */
	if (power_mode != ATH9K_PM_AWAKE) {
		spin_lock(&common->cc_lock);
		ath_hw_cycle_counters_update(common);
		memset(&common->cc_survey, 0, sizeof(common->cc_survey));
		memset(&common->cc_ani, 0, sizeof(common->cc_ani));
		spin_unlock(&common->cc_lock);
	}

 unlock:
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
}