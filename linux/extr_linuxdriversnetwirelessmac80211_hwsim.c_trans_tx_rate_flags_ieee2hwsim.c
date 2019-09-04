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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_tx_rate {int flags; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_160_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_DUP_DATA ; 
 int IEEE80211_TX_RC_GREEN_FIELD ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_USE_CTS_PROTECT ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_160_MHZ_WIDTH ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_DUP_DATA ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_GREEN_FIELD ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_MCS ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_USE_CTS_PROTECT ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_USE_RTS_CTS ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_USE_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  MAC80211_HWSIM_TX_RC_VHT_MCS ; 

__attribute__((used)) static inline u16 trans_tx_rate_flags_ieee2hwsim(struct ieee80211_tx_rate *rate)
{
	u16 result = 0;

	if (rate->flags & IEEE80211_TX_RC_USE_RTS_CTS)
		result |= MAC80211_HWSIM_TX_RC_USE_RTS_CTS;
	if (rate->flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		result |= MAC80211_HWSIM_TX_RC_USE_CTS_PROTECT;
	if (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		result |= MAC80211_HWSIM_TX_RC_USE_SHORT_PREAMBLE;
	if (rate->flags & IEEE80211_TX_RC_MCS)
		result |= MAC80211_HWSIM_TX_RC_MCS;
	if (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
		result |= MAC80211_HWSIM_TX_RC_GREEN_FIELD;
	if (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		result |= MAC80211_HWSIM_TX_RC_40_MHZ_WIDTH;
	if (rate->flags & IEEE80211_TX_RC_DUP_DATA)
		result |= MAC80211_HWSIM_TX_RC_DUP_DATA;
	if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		result |= MAC80211_HWSIM_TX_RC_SHORT_GI;
	if (rate->flags & IEEE80211_TX_RC_VHT_MCS)
		result |= MAC80211_HWSIM_TX_RC_VHT_MCS;
	if (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		result |= MAC80211_HWSIM_TX_RC_80_MHZ_WIDTH;
	if (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		result |= MAC80211_HWSIM_TX_RC_160_MHZ_WIDTH;

	return result;
}