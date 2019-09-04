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
typedef  int u8 ;
typedef  int u16 ;
struct rtl_priv {TYPE_1__* cfg; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int* maps; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t EFUSE_ACCESS ; 
 size_t EFUSE_ANA8M ; 
 size_t EFUSE_CLK ; 
 size_t EFUSE_FEN_ELDR ; 
 size_t EFUSE_LOADER_CLK_EN ; 
 size_t EFUSE_PWC_EV12V ; 
 size_t EFUSE_TEST ; 
 scalar_t__ HARDWARE_TYPE_RTL8192CE ; 
 scalar_t__ HARDWARE_TYPE_RTL8192DE ; 
 scalar_t__ HARDWARE_TYPE_RTL8192SE ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 size_t SYS_CLK ; 
 size_t SYS_FUNC_EN ; 
 size_t SYS_ISO_CTRL ; 
 int VOLTAGE_V25 ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int rtl_read_word (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int,int) ; 

void efuse_power_switch(struct ieee80211_hw *hw, u8 write, u8 pwrstate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tempval;
	u16 tmpv16;

	if (pwrstate && (rtlhal->hw_type != HARDWARE_TYPE_RTL8192SE)) {
		if (rtlhal->hw_type != HARDWARE_TYPE_RTL8192CE &&
		    rtlhal->hw_type != HARDWARE_TYPE_RTL8192DE) {
			rtl_write_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_ACCESS], 0x69);
		} else {
			tmpv16 =
			  rtl_read_word(rtlpriv,
					rtlpriv->cfg->maps[SYS_ISO_CTRL]);
			if (!(tmpv16 & rtlpriv->cfg->maps[EFUSE_PWC_EV12V])) {
				tmpv16 |= rtlpriv->cfg->maps[EFUSE_PWC_EV12V];
				rtl_write_word(rtlpriv,
					       rtlpriv->cfg->maps[SYS_ISO_CTRL],
					       tmpv16);
			}
		}
		tmpv16 = rtl_read_word(rtlpriv,
				       rtlpriv->cfg->maps[SYS_FUNC_EN]);
		if (!(tmpv16 & rtlpriv->cfg->maps[EFUSE_FEN_ELDR])) {
			tmpv16 |= rtlpriv->cfg->maps[EFUSE_FEN_ELDR];
			rtl_write_word(rtlpriv,
				       rtlpriv->cfg->maps[SYS_FUNC_EN], tmpv16);
		}

		tmpv16 = rtl_read_word(rtlpriv, rtlpriv->cfg->maps[SYS_CLK]);
		if ((!(tmpv16 & rtlpriv->cfg->maps[EFUSE_LOADER_CLK_EN])) ||
		    (!(tmpv16 & rtlpriv->cfg->maps[EFUSE_ANA8M]))) {
			tmpv16 |= (rtlpriv->cfg->maps[EFUSE_LOADER_CLK_EN] |
				   rtlpriv->cfg->maps[EFUSE_ANA8M]);
			rtl_write_word(rtlpriv,
				       rtlpriv->cfg->maps[SYS_CLK], tmpv16);
		}
	}

	if (pwrstate) {
		if (write) {
			tempval = rtl_read_byte(rtlpriv,
						rtlpriv->cfg->maps[EFUSE_TEST] +
						3);

			if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
				tempval &= ~(BIT(3) | BIT(4) | BIT(5) | BIT(6));
				tempval |= (VOLTAGE_V25 << 3);
			} else if (rtlhal->hw_type != HARDWARE_TYPE_RTL8192SE) {
				tempval &= 0x0F;
				tempval |= (VOLTAGE_V25 << 4);
			}

			rtl_write_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_TEST] + 3,
				       (tempval | 0x80));
		}

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE) {
			rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CLK],
				       0x03);
		}
	} else {
		if (rtlhal->hw_type != HARDWARE_TYPE_RTL8192CE &&
		    rtlhal->hw_type != HARDWARE_TYPE_RTL8192DE)
			rtl_write_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_ACCESS], 0);

		if (write) {
			tempval = rtl_read_byte(rtlpriv,
						rtlpriv->cfg->maps[EFUSE_TEST] +
						3);
			rtl_write_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_TEST] + 3,
				       (tempval & 0x7F));
		}

		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE) {
			rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CLK],
				       0x02);
		}
	}
}