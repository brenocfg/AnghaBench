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
typedef  size_t u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t rtl_get_bbreg (struct ieee80211_hw*,size_t,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92d_phy_save_adda_registers(struct ieee80211_hw *hw,
					    u32 *adda_reg, u32 *adda_backup,
					    u32 regnum)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Save ADDA parameters.\n");
	for (i = 0; i < regnum; i++)
		adda_backup[i] = rtl_get_bbreg(hw, adda_reg[i], MASKDWORD);
}