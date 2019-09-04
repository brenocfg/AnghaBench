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
typedef  int u32 ;
struct ath_hw {scalar_t__ opmode; scalar_t__ is_monitoring; } ;
struct ath9k_htc_priv {int rxfilter; int nvifs; TYPE_1__* hw; struct ath_hw* ah; } ;
struct TYPE_2__ {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int ATH9K_RX_FILTER_BCAST ; 
 int ATH9K_RX_FILTER_BEACON ; 
 int ATH9K_RX_FILTER_COMP_BAR ; 
 int ATH9K_RX_FILTER_CONTROL ; 
 int ATH9K_RX_FILTER_MCAST ; 
 int ATH9K_RX_FILTER_MCAST_BCAST_ALL ; 
 int ATH9K_RX_FILTER_MYBEACON ; 
 int ATH9K_RX_FILTER_PHYERR ; 
 int ATH9K_RX_FILTER_PHYRADAR ; 
 int ATH9K_RX_FILTER_PROBEREQ ; 
 int ATH9K_RX_FILTER_PROM ; 
 int ATH9K_RX_FILTER_PSPOLL ; 
 int ATH9K_RX_FILTER_UCAST ; 
 int ATH9K_RX_FILTER_UNCOMP_BA_BAR ; 
 int FIF_BCN_PRBRESP_PROMISC ; 
 int FIF_CONTROL ; 
 int FIF_OTHER_BSS ; 
 int FIF_PROBE_REQ ; 
 int FIF_PSPOLL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int ath9k_hw_getrxfilter (struct ath_hw*) ; 
 scalar_t__ conf_is_ht (int /*<<< orphan*/ *) ; 

u32 ath9k_htc_calcrxfilter(struct ath9k_htc_priv *priv)
{
#define	RX_FILTER_PRESERVE (ATH9K_RX_FILTER_PHYERR | ATH9K_RX_FILTER_PHYRADAR)

	struct ath_hw *ah = priv->ah;
	u32 rfilt;

	rfilt = (ath9k_hw_getrxfilter(ah) & RX_FILTER_PRESERVE)
		| ATH9K_RX_FILTER_UCAST | ATH9K_RX_FILTER_BCAST
		| ATH9K_RX_FILTER_MCAST;

	if (priv->rxfilter & FIF_PROBE_REQ)
		rfilt |= ATH9K_RX_FILTER_PROBEREQ;

	if (ah->is_monitoring)
		rfilt |= ATH9K_RX_FILTER_PROM;

	if (priv->rxfilter & FIF_CONTROL)
		rfilt |= ATH9K_RX_FILTER_CONTROL;

	if ((ah->opmode == NL80211_IFTYPE_STATION) &&
	    (priv->nvifs <= 1) &&
	    !(priv->rxfilter & FIF_BCN_PRBRESP_PROMISC))
		rfilt |= ATH9K_RX_FILTER_MYBEACON;
	else
		rfilt |= ATH9K_RX_FILTER_BEACON;

	if (conf_is_ht(&priv->hw->conf)) {
		rfilt |= ATH9K_RX_FILTER_COMP_BAR;
		rfilt |= ATH9K_RX_FILTER_UNCOMP_BA_BAR;
	}

	if (priv->rxfilter & FIF_PSPOLL)
		rfilt |= ATH9K_RX_FILTER_PSPOLL;

	if (priv->nvifs > 1 || priv->rxfilter & FIF_OTHER_BSS)
		rfilt |= ATH9K_RX_FILTER_MCAST_BCAST_ALL;

	return rfilt;

#undef RX_FILTER_PRESERVE
}