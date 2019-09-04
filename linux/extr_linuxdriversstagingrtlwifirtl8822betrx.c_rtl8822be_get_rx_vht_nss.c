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
typedef  scalar_t__ u8 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ DESC_RATEVHT1SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT1SS_MCS9 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS9 ; 
 scalar_t__ GET_RX_DESC_RX_RATE (scalar_t__*) ; 

__attribute__((used)) static u8 rtl8822be_get_rx_vht_nss(struct ieee80211_hw *hw, u8 *pdesc)
{
	u8 rx_rate = 0;
	u8 vht_nss = 0;

	rx_rate = GET_RX_DESC_RX_RATE(pdesc);

	if (rx_rate >= DESC_RATEVHT1SS_MCS0 &&
	    rx_rate <= DESC_RATEVHT1SS_MCS9)
		vht_nss = 1;
	else if ((rx_rate >= DESC_RATEVHT2SS_MCS0) &&
		 (rx_rate <= DESC_RATEVHT2SS_MCS9))
		vht_nss = 2;

	return vht_nss;
}