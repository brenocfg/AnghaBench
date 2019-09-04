#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int short_repeat; int count; int endless; int period; int fft_period; scalar_t__ enabled; } ;
struct TYPE_13__ {TYPE_5__ spec_config; TYPE_7__* ah; } ;
struct TYPE_11__ {int /*<<< orphan*/  count; } ;
struct TYPE_9__ {int slottime; int /*<<< orphan*/ ** bslot; } ;
struct ath_softc {TYPE_6__ spec_priv; TYPE_7__* sc_ah; TYPE_4__ ant_comb; TYPE_2__ beacon; } ;
struct TYPE_8__ {int /*<<< orphan*/  timer; } ;
struct ath_common {int /*<<< orphan*/  bssidmask; int /*<<< orphan*/  last_rssi; TYPE_1__ ani; } ;
struct TYPE_10__ {int hw_caps; } ;
struct TYPE_14__ {TYPE_3__ caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int ATH9K_HW_CAP_ANT_DIV_COMB ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_INIT_COUNT ; 
 int /*<<< orphan*/  ATH_RSSI_DUMMY_MARKER ; 
 struct ath_common* ath9k_hw_common (TYPE_7__*) ; 
 int /*<<< orphan*/  ath_ani_calibrate ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_init_misc(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int i = 0;

	timer_setup(&common->ani.timer, ath_ani_calibrate, 0);

	common->last_rssi = ATH_RSSI_DUMMY_MARKER;
	eth_broadcast_addr(common->bssidmask);
	sc->beacon.slottime = 9;

	for (i = 0; i < ARRAY_SIZE(sc->beacon.bslot); i++)
		sc->beacon.bslot[i] = NULL;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)
		sc->ant_comb.count = ATH_ANT_DIV_COMB_INIT_COUNT;

	sc->spec_priv.ah = sc->sc_ah;
	sc->spec_priv.spec_config.enabled = 0;
	sc->spec_priv.spec_config.short_repeat = true;
	sc->spec_priv.spec_config.count = 8;
	sc->spec_priv.spec_config.endless = false;
	sc->spec_priv.spec_config.period = 0xFF;
	sc->spec_priv.spec_config.fft_period = 0xF;
}