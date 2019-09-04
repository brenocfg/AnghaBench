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
typedef  int u8 ;
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ cur_80_prime_sc; scalar_t__ cur_40_prime_sc; } ;

/* Variables and functions */
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
 scalar_t__ PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ PRIME_CHNL_OFFSET_UPPER ; 
 int VHT_DATA_SC_20_LOWER_OF_80MHZ ; 
 int VHT_DATA_SC_20_LOWEST_OF_80MHZ ; 
 int VHT_DATA_SC_20_UPPERST_OF_80MHZ ; 
 int VHT_DATA_SC_20_UPPER_OF_80MHZ ; 
 int VHT_DATA_SC_40_LOWER_OF_80MHZ ; 
 int VHT_DATA_SC_40_UPPER_OF_80MHZ ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 

__attribute__((used)) static u8 _rtl8821ae_phy_get_secondary_chnl(struct rtl_priv *rtlpriv)
{
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	u8 sc_set_40 = 0, sc_set_20 = 0;

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) {
		if (mac->cur_80_prime_sc == PRIME_CHNL_OFFSET_LOWER)
			sc_set_40 = VHT_DATA_SC_40_LOWER_OF_80MHZ;
		else if (mac->cur_80_prime_sc == PRIME_CHNL_OFFSET_UPPER)
			sc_set_40 = VHT_DATA_SC_40_UPPER_OF_80MHZ;
		else
			pr_err("SCMapping: Not Correct Primary40MHz Setting\n");

		if ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_LOWER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER))
			sc_set_20 = VHT_DATA_SC_20_LOWEST_OF_80MHZ;
		else if ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_UPPER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER))
			sc_set_20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		else if ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_LOWER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_UPPER))
			sc_set_20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		else if ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_UPPER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_UPPER))
			sc_set_20 = VHT_DATA_SC_20_UPPERST_OF_80MHZ;
		else
			pr_err("SCMapping: Not Correct Primary40MHz Setting\n");
	} else if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
		if (mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_UPPER)
			sc_set_20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		else if (mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_LOWER)
			sc_set_20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		else
			pr_err("SCMapping: Not Correct Primary40MHz Setting\n");
	}
	return (sc_set_40 << 4) | sc_set_20;
}