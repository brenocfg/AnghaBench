#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct ath_common {TYPE_1__ ani; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void ath_stop_ani(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, ANI, "Stopping ANI\n");
	del_timer_sync(&common->ani.timer);
}