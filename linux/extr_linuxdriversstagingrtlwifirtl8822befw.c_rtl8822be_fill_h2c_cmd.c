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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int /*<<< orphan*/  fw_ready; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  _rtl8822be_fill_h2c_command (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8822be_fill_h2c_cmd(struct ieee80211_hw *hw, u8 element_id, u32 cmd_len,
			    u8 *cmdbuffer)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tmp_cmdbuf[8];

	if (!rtlhal->fw_ready) {
		WARN_ONCE(true,
			  "return H2C cmd because of Fw download fail!!!\n");
		return;
	}

	memset(tmp_cmdbuf, 0, 8);
	memcpy(tmp_cmdbuf, cmdbuffer, cmd_len);

	RT_TRACE(rtlpriv, COMP_CMD, DBG_DMESG,
		 "h2c cmd: len=%d %02X%02X%02X%02X %02X%02X%02X%02X\n", cmd_len,
		 tmp_cmdbuf[2], tmp_cmdbuf[1], tmp_cmdbuf[0], element_id,
		 tmp_cmdbuf[6], tmp_cmdbuf[5], tmp_cmdbuf[4], tmp_cmdbuf[3]);

	_rtl8822be_fill_h2c_command(hw, element_id, cmd_len, tmp_cmdbuf);
}