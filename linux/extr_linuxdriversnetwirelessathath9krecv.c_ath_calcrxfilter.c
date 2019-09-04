#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_16__ {scalar_t__ width; } ;
struct ath_softc {int /*<<< orphan*/  chan_lock; TYPE_7__* sc_ah; TYPE_5__* cur_chan; TYPE_4__ cur_chandef; TYPE_2__* hw; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct TYPE_18__ {scalar_t__ macVersion; } ;
struct TYPE_15__ {scalar_t__ enabled; } ;
struct TYPE_19__ {scalar_t__ opmode; TYPE_6__ hw_version; TYPE_3__ dynack; scalar_t__ is_monitoring; } ;
struct TYPE_17__ {int rxfilter; int nvifs; } ;
struct TYPE_13__ {scalar_t__ radar_enabled; } ;
struct TYPE_14__ {TYPE_1__ conf; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9462 (TYPE_7__*) ; 
 scalar_t__ AR_SREV_9531 (TYPE_7__*) ; 
 scalar_t__ AR_SREV_9550 (TYPE_7__*) ; 
 scalar_t__ AR_SREV_9561 (TYPE_7__*) ; 
 scalar_t__ AR_SREV_9565 (TYPE_7__*) ; 
 scalar_t__ AR_SREV_VERSION_9160 ; 
 int ATH9K_RX_FILTER_4ADDRESS ; 
 int ATH9K_RX_FILTER_BCAST ; 
 int ATH9K_RX_FILTER_BEACON ; 
 int ATH9K_RX_FILTER_COMP_BAR ; 
 int ATH9K_RX_FILTER_CONTROL ; 
 int ATH9K_RX_FILTER_CONTROL_WRAPPER ; 
 int ATH9K_RX_FILTER_MCAST ; 
 int ATH9K_RX_FILTER_MCAST_BCAST_ALL ; 
 int ATH9K_RX_FILTER_MYBEACON ; 
 int ATH9K_RX_FILTER_PHYERR ; 
 int ATH9K_RX_FILTER_PHYRADAR ; 
 int ATH9K_RX_FILTER_PROBEREQ ; 
 int ATH9K_RX_FILTER_PROM ; 
 int ATH9K_RX_FILTER_PSPOLL ; 
 int ATH9K_RX_FILTER_UCAST ; 
 int /*<<< orphan*/  ATH_OP_SCANNING ; 
 int /*<<< orphan*/  CONFIG_ATH9K_TX99 ; 
 int FIF_BCN_PRBRESP_PROMISC ; 
 int FIF_CONTROL ; 
 int FIF_OTHER_BSS ; 
 int FIF_PROBE_REQ ; 
 int FIF_PSPOLL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_OCB ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 struct ath_common* ath9k_hw_common (TYPE_7__*) ; 
 scalar_t__ ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u32 ath_calcrxfilter(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	u32 rfilt;

	if (IS_ENABLED(CONFIG_ATH9K_TX99))
		return 0;

	rfilt = ATH9K_RX_FILTER_UCAST | ATH9K_RX_FILTER_BCAST
		| ATH9K_RX_FILTER_MCAST;

	/* if operating on a DFS channel, enable radar pulse detection */
	if (sc->hw->conf.radar_enabled)
		rfilt |= ATH9K_RX_FILTER_PHYRADAR | ATH9K_RX_FILTER_PHYERR;

	spin_lock_bh(&sc->chan_lock);

	if (sc->cur_chan->rxfilter & FIF_PROBE_REQ)
		rfilt |= ATH9K_RX_FILTER_PROBEREQ;

	if (sc->sc_ah->is_monitoring)
		rfilt |= ATH9K_RX_FILTER_PROM;

	if ((sc->cur_chan->rxfilter & FIF_CONTROL) ||
	    sc->sc_ah->dynack.enabled)
		rfilt |= ATH9K_RX_FILTER_CONTROL;

	if ((sc->sc_ah->opmode == NL80211_IFTYPE_STATION) &&
	    (sc->cur_chan->nvifs <= 1) &&
	    !(sc->cur_chan->rxfilter & FIF_BCN_PRBRESP_PROMISC))
		rfilt |= ATH9K_RX_FILTER_MYBEACON;
	else if (sc->sc_ah->opmode != NL80211_IFTYPE_OCB)
		rfilt |= ATH9K_RX_FILTER_BEACON;

	if ((sc->sc_ah->opmode == NL80211_IFTYPE_AP) ||
	    (sc->cur_chan->rxfilter & FIF_PSPOLL))
		rfilt |= ATH9K_RX_FILTER_PSPOLL;

	if (sc->cur_chandef.width != NL80211_CHAN_WIDTH_20_NOHT)
		rfilt |= ATH9K_RX_FILTER_COMP_BAR;

	if (sc->cur_chan->nvifs > 1 || (sc->cur_chan->rxfilter & FIF_OTHER_BSS)) {
		/* This is needed for older chips */
		if (sc->sc_ah->hw_version.macVersion <= AR_SREV_VERSION_9160)
			rfilt |= ATH9K_RX_FILTER_PROM;
		rfilt |= ATH9K_RX_FILTER_MCAST_BCAST_ALL;
	}

	if (AR_SREV_9550(sc->sc_ah) || AR_SREV_9531(sc->sc_ah) ||
	    AR_SREV_9561(sc->sc_ah))
		rfilt |= ATH9K_RX_FILTER_4ADDRESS;

	if (AR_SREV_9462(sc->sc_ah) || AR_SREV_9565(sc->sc_ah))
		rfilt |= ATH9K_RX_FILTER_CONTROL_WRAPPER;

	if (ath9k_is_chanctx_enabled() &&
	    test_bit(ATH_OP_SCANNING, &common->op_flags))
		rfilt |= ATH9K_RX_FILTER_BEACON;

	spin_unlock_bh(&sc->chan_lock);

	return rfilt;

}