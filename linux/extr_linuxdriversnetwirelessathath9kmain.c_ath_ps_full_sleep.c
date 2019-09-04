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
struct timer_list {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int /*<<< orphan*/  cc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_PM_FULL_SLEEP ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setrxabort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_stopdmarecv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ath_hw_cycle_counters_update (struct ath_common*) ; 
 struct ath_softc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ath_softc* sc ; 
 int /*<<< orphan*/  sleep_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ath_ps_full_sleep(struct timer_list *t)
{
	struct ath_softc *sc = from_timer(sc, t, sleep_timer);
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned long flags;
	bool reset;

	spin_lock_irqsave(&common->cc_lock, flags);
	ath_hw_cycle_counters_update(common);
	spin_unlock_irqrestore(&common->cc_lock, flags);

	ath9k_hw_setrxabort(sc->sc_ah, 1);
	ath9k_hw_stopdmarecv(sc->sc_ah, &reset);

	ath9k_hw_setpower(sc->sc_ah, ATH9K_PM_FULL_SLEEP);
}