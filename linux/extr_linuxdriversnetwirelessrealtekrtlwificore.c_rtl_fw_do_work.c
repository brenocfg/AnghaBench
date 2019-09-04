#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fwsize; scalar_t__ wowlan_fwsize; int /*<<< orphan*/  wowlan_firmware; int /*<<< orphan*/  pfirmware; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct rtl_priv {scalar_t__ max_fw_size; TYPE_3__ rtlhal; TYPE_2__* cfg; TYPE_1__ io; int /*<<< orphan*/  firmware_loading_complete; } ;
struct ieee80211_hw {int dummy; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ alt_fw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl_fw_do_work(const struct firmware *firmware, void *context,
			   bool is_wow)
{
	struct ieee80211_hw *hw = context;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int err;

	RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
		 "Firmware callback routine entered!\n");
	complete(&rtlpriv->firmware_loading_complete);
	if (!firmware) {
		if (rtlpriv->cfg->alt_fw_name) {
			err = request_firmware(&firmware,
					       rtlpriv->cfg->alt_fw_name,
					       rtlpriv->io.dev);
			pr_info("Loading alternative firmware %s\n",
				rtlpriv->cfg->alt_fw_name);
			if (!err)
				goto found_alt;
		}
		pr_err("Selected firmware is not available\n");
		rtlpriv->max_fw_size = 0;
		return;
	}
found_alt:
	if (firmware->size > rtlpriv->max_fw_size) {
		pr_err("Firmware is too big!\n");
		release_firmware(firmware);
		return;
	}
	if (!is_wow) {
		memcpy(rtlpriv->rtlhal.pfirmware, firmware->data,
		       firmware->size);
		rtlpriv->rtlhal.fwsize = firmware->size;
	} else {
		memcpy(rtlpriv->rtlhal.wowlan_firmware, firmware->data,
		       firmware->size);
		rtlpriv->rtlhal.wowlan_fwsize = firmware->size;
	}
	release_firmware(firmware);
}