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
struct TYPE_2__ {scalar_t__ pfirmware; } ;
struct rtl_priv {scalar_t__ max_fw_size; TYPE_1__ rtlhal; int /*<<< orphan*/  firmware_loading_complete; } ;
struct rt_firmware {scalar_t__ sz_fw_tmpbufferlen; int /*<<< orphan*/  sz_fw_tmpbuffer; } ;
struct ieee80211_hw {int dummy; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92se_fw_cb(const struct firmware *firmware, void *context)
{
	struct ieee80211_hw *hw = context;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rt_firmware *pfirmware = NULL;
	char *fw_name = "rtlwifi/rtl8192sefw.bin";

	RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
			 "Firmware callback routine entered!\n");
	complete(&rtlpriv->firmware_loading_complete);
	if (!firmware) {
		pr_err("Firmware %s not available\n", fw_name);
		rtlpriv->max_fw_size = 0;
		return;
	}
	if (firmware->size > rtlpriv->max_fw_size) {
		pr_err("Firmware is too big!\n");
		rtlpriv->max_fw_size = 0;
		release_firmware(firmware);
		return;
	}
	pfirmware = (struct rt_firmware *)rtlpriv->rtlhal.pfirmware;
	memcpy(pfirmware->sz_fw_tmpbuffer, firmware->data, firmware->size);
	pfirmware->sz_fw_tmpbufferlen = firmware->size;
	release_firmware(firmware);
}