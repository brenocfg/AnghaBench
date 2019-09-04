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
typedef  scalar_t__ u32 ;
struct rtlwifi_firmware_header {int /*<<< orphan*/  signature; int /*<<< orphan*/  version; int /*<<< orphan*/  subversion; } ;
struct rtl_priv {scalar_t__ max_fw_size; TYPE_2__* cfg; } ;
struct rtl_hal {int version; scalar_t__ fwsize; int /*<<< orphan*/ * pfirmware; int /*<<< orphan*/  fw_subversion; int /*<<< orphan*/  fw_version; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8723e { ____Placeholder_version_8723e } version_8723e ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ (* is_fw_header ) (struct rtlwifi_firmware_header*) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  REG_MCUFWDL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl8723_enable_fw_download (struct ieee80211_hw*,int) ; 
 int rtl8723_fw_free_to_go (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8723_write_fw (struct ieee80211_hw*,int,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl8723ae_firmware_selfreset (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723be_firmware_selfreset (struct ieee80211_hw*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct rtlwifi_firmware_header*) ; 

int rtl8723_download_fw(struct ieee80211_hw *hw,
			bool is_8723be, int max_count)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtlwifi_firmware_header *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	int err;
	enum version_8723e version = rtlhal->version;
	int max_page;

	if (rtlpriv->max_fw_size == 0 || !rtlhal->pfirmware)
		return 1;

	pfwheader = (struct rtlwifi_firmware_header *)rtlhal->pfirmware;
	rtlhal->fw_version = le16_to_cpu(pfwheader->version);
	rtlhal->fw_subversion = pfwheader->subversion;
	pfwdata = rtlhal->pfirmware;
	fwsize = rtlhal->fwsize;

	if (!is_8723be)
		max_page = 6;
	else
		max_page = 8;
	if (rtlpriv->cfg->ops->is_fw_header(pfwheader)) {
		RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD,
			 "Firmware Version(%d), Signature(%#x), Size(%d)\n",
			 pfwheader->version, pfwheader->signature,
			 (int)sizeof(struct rtlwifi_firmware_header));

		pfwdata = pfwdata + sizeof(struct rtlwifi_firmware_header);
		fwsize = fwsize - sizeof(struct rtlwifi_firmware_header);
	}

	if (rtl_read_byte(rtlpriv, REG_MCUFWDL)&BIT(7)) {
		if (is_8723be)
			rtl8723be_firmware_selfreset(hw);
		else
			rtl8723ae_firmware_selfreset(hw);
		rtl_write_byte(rtlpriv, REG_MCUFWDL, 0x00);
	}
	rtl8723_enable_fw_download(hw, true);
	rtl8723_write_fw(hw, version, pfwdata, fwsize, max_page);
	rtl8723_enable_fw_download(hw, false);

	err = rtl8723_fw_free_to_go(hw, is_8723be, max_count);
	if (err)
		pr_err("Firmware is not ready to run!\n");
	return 0;
}