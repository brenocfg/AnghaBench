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
struct ieee80211_tx_rate {int flags; } ;
struct ar9170 {int erp_mode; } ;

/* Variables and functions */
#define  CARL9170_ERP_AUTO 130 
#define  CARL9170_ERP_CTS 129 
#define  CARL9170_ERP_MAC80211 128 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 

__attribute__((used)) static bool carl9170_tx_cts_check(struct ar9170 *ar,
				  struct ieee80211_tx_rate *rate)
{
	switch (ar->erp_mode) {
	case CARL9170_ERP_AUTO:
	case CARL9170_ERP_MAC80211:
		if (!(rate->flags & IEEE80211_TX_RC_USE_CTS_PROTECT))
			break;

	case CARL9170_ERP_CTS:
		return true;

	default:
		break;
	}

	return false;
}