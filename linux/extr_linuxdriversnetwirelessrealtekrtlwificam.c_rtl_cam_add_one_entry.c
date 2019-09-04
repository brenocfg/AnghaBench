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
typedef  int u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int CFG_VALID ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_SEC ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int TOTAL_CAM_ENTRY ; 
 int /*<<< orphan*/  rtl_cam_program_entry (struct ieee80211_hw*,int,int*,int*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u8 rtl_cam_add_one_entry(struct ieee80211_hw *hw, u8 *mac_addr,
			 u32 ul_key_id, u32 ul_entry_idx, u32 ul_enc_alg,
			 u32 ul_default_key, u8 *key_content)
{
	u32 us_config;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
		 "EntryNo:%x, ulKeyId=%x, ulEncAlg=%x, ulUseDK=%x MacAddr %pM\n",
		 ul_entry_idx, ul_key_id, ul_enc_alg,
		 ul_default_key, mac_addr);

	if (ul_key_id == TOTAL_CAM_ENTRY) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "ulKeyId exceed!\n");
		return 0;
	}

	if (ul_default_key == 1)
		us_config = CFG_VALID | ((u16) (ul_enc_alg) << 2);
	else
		us_config = CFG_VALID | ((ul_enc_alg) << 2) | ul_key_id;

	rtl_cam_program_entry(hw, ul_entry_idx, mac_addr,
			      (u8 *)key_content, us_config);

	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, "end\n");

	return 1;

}