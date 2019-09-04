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
struct rtl_priv {TYPE_1__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int* maps; } ;

/* Variables and functions */
 size_t EFUSE_CTRL ; 
 size_t EFUSE_TEST ; 
 size_t SYS_FUNC_EN ; 
 size_t SYS_ISO_CTRL ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

void efuse_initialize(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bytetemp;
	u8 temp;

	bytetemp = rtl_read_byte(rtlpriv, rtlpriv->cfg->maps[SYS_FUNC_EN] + 1);
	temp = bytetemp | 0x20;
	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[SYS_FUNC_EN] + 1, temp);

	bytetemp = rtl_read_byte(rtlpriv, rtlpriv->cfg->maps[SYS_ISO_CTRL] + 1);
	temp = bytetemp & 0xFE;
	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[SYS_ISO_CTRL] + 1, temp);

	bytetemp = rtl_read_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST] + 3);
	temp = bytetemp | 0x80;
	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST] + 3, temp);

	rtl_write_byte(rtlpriv, 0x2F8, 0x3);

	rtl_write_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3, 0x72);

}