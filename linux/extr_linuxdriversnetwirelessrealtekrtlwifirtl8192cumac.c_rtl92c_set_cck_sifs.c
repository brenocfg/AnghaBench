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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_SIFS_CCK ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl92c_set_cck_sifs(struct ieee80211_hw *hw, u8 trx_sifs,
				u8 ctx_sifs)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_byte(rtlpriv, REG_SIFS_CCK, trx_sifs);
	rtl_write_byte(rtlpriv, (REG_SIFS_CCK + 1), ctx_sifs);
}