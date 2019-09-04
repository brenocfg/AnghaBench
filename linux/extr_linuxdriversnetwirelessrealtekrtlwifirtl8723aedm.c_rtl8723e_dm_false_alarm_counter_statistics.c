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
typedef  int u32 ;
struct false_alarm_statistics {int cnt_parity_fail; int cnt_rate_illegal; int cnt_crc8_fail; int cnt_mcs_fail; int cnt_ofdm_fail; int cnt_cck_fail; int cnt_all; } ;
struct rtl_priv {struct false_alarm_statistics falsealm_cnt; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RCCK0_FACOUNTERLOWER ; 
 int /*<<< orphan*/  RCCK0_FACOUNTERUPPER ; 
 int /*<<< orphan*/  RCCK0_FALSEALARMREPORT ; 
 int /*<<< orphan*/  ROFDM1_LSTF ; 
 int /*<<< orphan*/  ROFDM_PHYCOUNTER1 ; 
 int /*<<< orphan*/  ROFDM_PHYCOUNTER2 ; 
 int /*<<< orphan*/  ROFDM_PHYCOUNTER3 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl8723e_dm_false_alarm_counter_statistics(struct ieee80211_hw *hw)
{
	u32 ret_value;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
	    falsealm_cnt->cnt_rate_illegal +
	    falsealm_cnt->cnt_crc8_fail + falsealm_cnt->cnt_mcs_fail;

	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, BIT(14), 1);
	ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERLOWER, MASKBYTE0);
	falsealm_cnt->cnt_cck_fail = ret_value;

	ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERUPPER, MASKBYTE3);
	falsealm_cnt->cnt_cck_fail += (ret_value & 0xff) << 8;
	falsealm_cnt->cnt_all = (falsealm_cnt->cnt_parity_fail +
				 falsealm_cnt->cnt_rate_illegal +
				 falsealm_cnt->cnt_crc8_fail +
				 falsealm_cnt->cnt_mcs_fail +
				 falsealm_cnt->cnt_cck_fail);

	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 1);
	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 0);
	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 0);
	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 2);

	RT_TRACE(rtlpriv, COMP_DIG, DBG_TRACE,
		 "cnt_parity_fail = %d, cnt_rate_illegal = %d, cnt_crc8_fail = %d, cnt_mcs_fail = %d\n",
		 falsealm_cnt->cnt_parity_fail,
		 falsealm_cnt->cnt_rate_illegal,
		 falsealm_cnt->cnt_crc8_fail, falsealm_cnt->cnt_mcs_fail);

	RT_TRACE(rtlpriv, COMP_DIG, DBG_TRACE,
		 "cnt_ofdm_fail = %x, cnt_cck_fail = %x, cnt_all = %x\n",
		 falsealm_cnt->cnt_ofdm_fail,
		 falsealm_cnt->cnt_cck_fail, falsealm_cnt->cnt_all);
}