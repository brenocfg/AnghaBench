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
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int FEN_CPUEN ; 
 int IMEM_RDY ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_CLKR ; 
 int SYS_CPU_CLKSEL ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  _rtl92s_fw_set_rqpn (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int rtl_read_word (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool _rtl92s_firmware_enable_cpu(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 ichecktime = 200;
	u16 tmpu2b;
	u8 tmpu1b, cpustatus = 0;

	_rtl92s_fw_set_rqpn(hw);

	/* Enable CPU. */
	tmpu1b = rtl_read_byte(rtlpriv, SYS_CLKR);
	/* AFE source */
	rtl_write_byte(rtlpriv, SYS_CLKR, (tmpu1b | SYS_CPU_CLKSEL));

	tmpu2b = rtl_read_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_write_word(rtlpriv, REG_SYS_FUNC_EN, (tmpu2b | FEN_CPUEN));

	/* Polling IMEM Ready after CPU has refilled. */
	do {
		cpustatus = rtl_read_byte(rtlpriv, TCR);
		if (cpustatus & IMEM_RDY) {
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				 "IMEM Ready after CPU has refilled\n");
			break;
		}

		udelay(100);
	} while (ichecktime--);

	if (!(cpustatus & IMEM_RDY))
		return false;

	return true;
}