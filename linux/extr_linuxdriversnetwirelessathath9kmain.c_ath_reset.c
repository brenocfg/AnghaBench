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
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_HW_RESET ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_kill_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int ath_reset_internal (struct ath_softc*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ath_reset(struct ath_softc *sc, struct ath9k_channel *hchan)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int r;

	ath9k_hw_kill_interrupts(sc->sc_ah);
	set_bit(ATH_OP_HW_RESET, &common->op_flags);

	ath9k_ps_wakeup(sc);
	r = ath_reset_internal(sc, hchan);
	ath9k_ps_restore(sc);

	return r;
}