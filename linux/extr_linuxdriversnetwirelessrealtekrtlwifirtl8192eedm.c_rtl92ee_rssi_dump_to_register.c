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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_cfo_tail; int /*<<< orphan*/ * rx_cfo_short; scalar_t__* rx_snr_db; int /*<<< orphan*/ * rx_evm_dbm; int /*<<< orphan*/ * rx_rssi_percentage; } ;
struct rtl_priv {TYPE_1__ stats; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_CFOLONGDUMP ; 
 int /*<<< orphan*/  RA_CFOSHORTDUMP ; 
 int /*<<< orphan*/  RA_RSSIDUMP ; 
 int /*<<< orphan*/  RA_RXSNRDUMP ; 
 int /*<<< orphan*/  RB_CFOLONGDUMP ; 
 int /*<<< orphan*/  RB_CFOSHORTDUMP ; 
 int /*<<< orphan*/  RB_RSSIDUMP ; 
 int /*<<< orphan*/  RB_RXSNRDUMP ; 
 int /*<<< orphan*/  RS1_RXEVMDUMP ; 
 int /*<<< orphan*/  RS2_RXEVMDUMP ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl92ee_rssi_dump_to_register(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_byte(rtlpriv, RA_RSSIDUMP,
		       rtlpriv->stats.rx_rssi_percentage[0]);
	rtl_write_byte(rtlpriv, RB_RSSIDUMP,
		       rtlpriv->stats.rx_rssi_percentage[1]);
	/*It seems the following values are not initialized.
	  *According to Windows code,
	  *these value will only be valid with JAGUAR chips
	  */
	/* Rx EVM */
	rtl_write_byte(rtlpriv, RS1_RXEVMDUMP, rtlpriv->stats.rx_evm_dbm[0]);
	rtl_write_byte(rtlpriv, RS2_RXEVMDUMP, rtlpriv->stats.rx_evm_dbm[1]);
	/* Rx SNR */
	rtl_write_byte(rtlpriv, RA_RXSNRDUMP,
		       (u8)(rtlpriv->stats.rx_snr_db[0]));
	rtl_write_byte(rtlpriv, RB_RXSNRDUMP,
		       (u8)(rtlpriv->stats.rx_snr_db[1]));
	/* Rx Cfo_Short */
	rtl_write_word(rtlpriv, RA_CFOSHORTDUMP,
		       rtlpriv->stats.rx_cfo_short[0]);
	rtl_write_word(rtlpriv, RB_CFOSHORTDUMP,
		       rtlpriv->stats.rx_cfo_short[1]);
	/* Rx Cfo_Tail */
	rtl_write_word(rtlpriv, RA_CFOLONGDUMP, rtlpriv->stats.rx_cfo_tail[0]);
	rtl_write_word(rtlpriv, RB_CFOLONGDUMP, rtlpriv->stats.rx_cfo_tail[1]);
}