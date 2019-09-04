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
struct dig_t {int cur_igvalue; int pre_igvalue; int /*<<< orphan*/  back_val; } ;
struct rtl_priv {struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  ROFDM0_XAAGCCORE1 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 

void rtl88e_dm_write_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_dig = &rtlpriv->dm_digtable;

	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "cur_igvalue = 0x%x, pre_igvalue = 0x%x, backoff_val = %d\n",
		 dm_dig->cur_igvalue, dm_dig->pre_igvalue,
		 dm_dig->back_val);

	if (dm_dig->cur_igvalue > 0x3f)
		dm_dig->cur_igvalue = 0x3f;
	if (dm_dig->pre_igvalue != dm_dig->cur_igvalue) {
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f,
			      dm_dig->cur_igvalue);

		dm_dig->pre_igvalue = dm_dig->cur_igvalue;
	}
}