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
typedef  scalar_t__ u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BEACON_QUEUE ; 
 int BIT (int) ; 
 scalar_t__ REG_RX_RXBD_NUM_8822B ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 

void rtl8822be_tx_polling(struct ieee80211_hw *hw, u8 hw_queue)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (hw_queue == BEACON_QUEUE) {
		/* kick start */
		rtl_write_byte(
			rtlpriv, REG_RX_RXBD_NUM_8822B + 1,
			rtl_read_byte(rtlpriv, REG_RX_RXBD_NUM_8822B + 1) |
				BIT(4));
	}
}