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
struct ath_softc {int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  sc_ah; } ;
typedef  enum ath9k_power_mode { ____Placeholder_ath9k_power_mode } ath9k_power_mode ;

/* Variables and functions */
 int ath9k_hw_setpower (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool ath9k_setpower(struct ath_softc *sc, enum ath9k_power_mode mode)
{
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	ret = ath9k_hw_setpower(sc->sc_ah, mode);
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	return ret;
}