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
typedef  size_t u8 ;
struct rtl_phy {TYPE_1__* iqk_matrix; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct iqk_matrix_regs {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int** value; int iqk_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_IQK ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 size_t IQK_MATRIX_SETTINGS_NUM ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8821ae_reset_iqk_result(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i;

	RT_TRACE(rtlpriv, COMP_IQK, DBG_LOUD,
		 "rtl8812ae_dm_reset_iqk_result:: settings regs %d default regs %d\n",
		 (int)(sizeof(rtlphy->iqk_matrix) /
		 sizeof(struct iqk_matrix_regs)),
		 IQK_MATRIX_SETTINGS_NUM);

	for (i = 0; i < IQK_MATRIX_SETTINGS_NUM; i++) {
		rtlphy->iqk_matrix[i].value[0][0] = 0x100;
		rtlphy->iqk_matrix[i].value[0][2] = 0x100;
		rtlphy->iqk_matrix[i].value[0][4] = 0x100;
		rtlphy->iqk_matrix[i].value[0][6] = 0x100;

		rtlphy->iqk_matrix[i].value[0][1] = 0x0;
		rtlphy->iqk_matrix[i].value[0][3] = 0x0;
		rtlphy->iqk_matrix[i].value[0][5] = 0x0;
		rtlphy->iqk_matrix[i].value[0][7] = 0x0;

		rtlphy->iqk_matrix[i].iqk_done = false;
	}
}