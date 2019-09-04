#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_vif {int av_bslot; int /*<<< orphan*/  tsf_adjust; } ;
struct TYPE_4__ {TYPE_1__** bslot; } ;
struct ath_softc {TYPE_2__ beacon; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
struct ath_beacon_config {int beacon_interval; } ;
typedef  int s64 ;
struct TYPE_3__ {scalar_t__ drv_priv; } ;

/* Variables and functions */
 int ATH_BCBUF ; 
 int /*<<< orphan*/  CONFIG ; 
 int TU_TO_USEC (int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,long long,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void ath9k_set_tsfadjust(struct ath_softc *sc,
				struct ath_beacon_config *cur_conf)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	s64 tsfadjust;
	int slot;

	for (slot = 0; slot < ATH_BCBUF; slot++) {
		struct ath_vif *avp;

		if (!sc->beacon.bslot[slot])
			continue;

		avp = (void *)sc->beacon.bslot[slot]->drv_priv;

		/* tsf_adjust is added to the TSF value. We send out the
		 * beacon late, so need to adjust the TSF starting point to be
		 * later in time (i.e. the theoretical first beacon has a TSF
		 * of 0 after correction).
		 */
		tsfadjust = cur_conf->beacon_interval * avp->av_bslot;
		tsfadjust = -TU_TO_USEC(tsfadjust) / ATH_BCBUF;
		avp->tsf_adjust = cpu_to_le64(tsfadjust);

		ath_dbg(common, CONFIG, "tsfadjust is: %lld for bslot: %d\n",
			(signed long long)tsfadjust, avp->av_bslot);
	}
}