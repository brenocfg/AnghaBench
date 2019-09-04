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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ cur_40_prime_sc; scalar_t__ cur_80_prime_sc; } ;

/* Variables and functions */
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_LOWER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_LOWEST_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_UPPERST_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_20_UPPER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_40_LOWER_OF_80MHZ ; 
 int /*<<< orphan*/  VHT_DATA_SC_40_UPPER_OF_80MHZ ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 

__attribute__((used)) static u8 _rtl8822be_phy_get_pri_ch_id(struct rtl_priv *rtlpriv)
{
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	u8 pri_ch_idx = 0;

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) {
		/* primary channel is at lower subband of 80MHz & 40MHz */
		if (mac->cur_40_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER &&
		    mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER) {
			pri_ch_idx = VHT_DATA_SC_20_LOWEST_OF_80MHZ;
		/* primary channel is at
		 * lower subband of 80MHz & upper subband of 40MHz
		 */
		} else if ((mac->cur_40_prime_sc ==
			    HAL_PRIME_CHNL_OFFSET_UPPER) &&
			   (mac->cur_80_prime_sc ==
			    HAL_PRIME_CHNL_OFFSET_LOWER)) {
			pri_ch_idx = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		/* primary channel is at
		 * upper subband of 80MHz & lower subband of 40MHz
		 */
		} else if ((mac->cur_40_prime_sc ==
			  HAL_PRIME_CHNL_OFFSET_LOWER) &&
			 (mac->cur_80_prime_sc ==
			  HAL_PRIME_CHNL_OFFSET_UPPER)) {
			pri_ch_idx = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		/* primary channel is at
		 * upper subband of 80MHz & upper subband of 40MHz
		 */
		} else if ((mac->cur_40_prime_sc ==
			    HAL_PRIME_CHNL_OFFSET_UPPER) &&
			   (mac->cur_80_prime_sc ==
			    HAL_PRIME_CHNL_OFFSET_UPPER)) {
			pri_ch_idx = VHT_DATA_SC_20_UPPERST_OF_80MHZ;
		} else {
			if (mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER)
				pri_ch_idx = VHT_DATA_SC_40_LOWER_OF_80MHZ;
			else if (mac->cur_80_prime_sc ==
				 HAL_PRIME_CHNL_OFFSET_UPPER)
				pri_ch_idx = VHT_DATA_SC_40_UPPER_OF_80MHZ;
		}
	} else if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
		/* primary channel is at upper subband of 40MHz */
		if (mac->cur_40_prime_sc == HAL_PRIME_CHNL_OFFSET_UPPER)
			pri_ch_idx = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		/* primary channel is at lower subband of 40MHz */
		else if (mac->cur_40_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER)
			pri_ch_idx = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		else
			;
	}

	return pri_ch_idx;
}