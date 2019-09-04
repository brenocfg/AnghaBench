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
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_tx99_stop (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_reset (struct ath_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_tx99_deinit(struct ath_softc *sc)
{
	ath_reset(sc, NULL);

	ath9k_ps_wakeup(sc);
	ath9k_tx99_stop(sc);
	ath9k_ps_restore(sc);
}