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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ASPM_L1_LATENCY ; 
 int BIT (int) ; 
 int _rtl8723be_dbi_read (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl8723be_dbi_write (struct rtl_priv*,int,int) ; 
 int _rtl8723be_mdio_read (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  _rtl8723be_mdio_write (struct rtl_priv*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8723be_enable_aspm_back_door(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tmp8 = 0;
	u16 tmp16 = 0;

	/* <Roger_Notes> Overwrite following ePHY parameter for
	 * some platform compatibility issue,
	 * especially when CLKReq is enabled, 2012.11.09.
	 */
	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x01);
	if (tmp16 != 0x0663)
		_rtl8723be_mdio_write(rtlpriv, 0x01, 0x0663);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x04);
	if (tmp16 != 0x7544)
		_rtl8723be_mdio_write(rtlpriv, 0x04, 0x7544);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x06);
	if (tmp16 != 0xB880)
		_rtl8723be_mdio_write(rtlpriv, 0x06, 0xB880);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x07);
	if (tmp16 != 0x4000)
		_rtl8723be_mdio_write(rtlpriv, 0x07, 0x4000);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x08);
	if (tmp16 != 0x9003)
		_rtl8723be_mdio_write(rtlpriv, 0x08, 0x9003);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x09);
	if (tmp16 != 0x0D03)
		_rtl8723be_mdio_write(rtlpriv, 0x09, 0x0D03);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x0A);
	if (tmp16 != 0x4037)
		_rtl8723be_mdio_write(rtlpriv, 0x0A, 0x4037);

	tmp16 = _rtl8723be_mdio_read(rtlpriv, 0x0B);
	if (tmp16 != 0x0070)
		_rtl8723be_mdio_write(rtlpriv, 0x0B, 0x0070);

	/* Configuration Space offset 0x70f BIT7 is used to control L0S */
	tmp8 = _rtl8723be_dbi_read(rtlpriv, 0x70f);
	_rtl8723be_dbi_write(rtlpriv, 0x70f, tmp8 | BIT(7) |
			     ASPM_L1_LATENCY << 3);

	/* Configuration Space offset 0x719 Bit3 is for L1
	 * BIT4 is for clock request
	 */
	tmp8 = _rtl8723be_dbi_read(rtlpriv, 0x719);
	_rtl8723be_dbi_write(rtlpriv, 0x719, tmp8 | BIT(3) | BIT(4));
}