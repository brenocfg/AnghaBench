#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_hal {scalar_t__ interfaceindex; int bandset; } ;
struct rtl_efuse {int txpwr_fromeprom; void* channel_plan; int /*<<< orphan*/  autoload_failflag; int /*<<< orphan*/ * dev_addr; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
#define  BAND_ON_2_4G 130 
#define  BAND_ON_5G 129 
#define  BAND_ON_BOTH 128 
 int /*<<< orphan*/  COMP_INIT ; 
 void* COUNTRY_CODE_FCC ; 
 void* COUNTRY_CODE_TELEC ; 
 int COUNTRY_CODE_WORLD_WIDE_13 ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int EEPROM_CHANNEL_PLAN ; 
 int EEPROM_CUSTOMER_ID ; 
 int EEPROM_DID ; 
 int EEPROM_MAC_ADDR_MAC0_92D ; 
 int EEPROM_MAC_ADDR_MAC1_92D ; 
 int EEPROM_SMID ; 
 int EEPROM_SVID ; 
 int EEPROM_VERSION ; 
 int EEPROM_VID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 int RTL8190_EEPROM_ID ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92de_efuse_update_chip_version (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92de_read_macphymode_and_bandtype (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92de_read_txpower_info (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 scalar_t__ rtl_get_hwinfo (struct ieee80211_hw*,struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92de_read_adapter_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int params[] = {RTL8190_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR_MAC0_92D,
			EEPROM_CHANNEL_PLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13};
	int i;
	u16 usvalue;
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	if (!hwinfo)
		return;

	if (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		goto exit;

	_rtl92de_efuse_update_chip_version(hw);
	_rtl92de_read_macphymode_and_bandtype(hw, hwinfo);

	/* Read Permanent MAC address for 2nd interface */
	if (rtlhal->interfaceindex != 0) {
		for (i = 0; i < 6; i += 2) {
			usvalue = *(u16 *)&hwinfo[EEPROM_MAC_ADDR_MAC1_92D + i];
			*((u16 *) (&rtlefuse->dev_addr[i])) = usvalue;
		}
	}
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR,
				      rtlefuse->dev_addr);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG, "%pM\n", rtlefuse->dev_addr);
	_rtl92de_read_txpower_info(hw, rtlefuse->autoload_failflag, hwinfo);

	/* Read Channel Plan */
	switch (rtlhal->bandset) {
	case BAND_ON_2_4G:
		rtlefuse->channel_plan = COUNTRY_CODE_TELEC;
		break;
	case BAND_ON_5G:
		rtlefuse->channel_plan = COUNTRY_CODE_FCC;
		break;
	case BAND_ON_BOTH:
		rtlefuse->channel_plan = COUNTRY_CODE_FCC;
		break;
	default:
		rtlefuse->channel_plan = COUNTRY_CODE_FCC;
		break;
	}
	rtlefuse->txpwr_fromeprom = true;
exit:
	kfree(hwinfo);
}