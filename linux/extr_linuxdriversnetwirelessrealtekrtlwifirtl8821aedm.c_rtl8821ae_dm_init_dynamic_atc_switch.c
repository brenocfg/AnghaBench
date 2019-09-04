#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cfo_threshold; int /*<<< orphan*/  atc_status; int /*<<< orphan*/  crystal_cap; } ;
struct TYPE_3__ {int /*<<< orphan*/  crystalcap; } ;
struct rtl_priv {TYPE_2__ dm; TYPE_1__ efuse; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CFO_THRESHOLD_XTAL ; 
 int /*<<< orphan*/  ROFDM1_CFOTRACKING ; 
 int /*<<< orphan*/  rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8821ae_dm_init_dynamic_atc_switch(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.crystal_cap = rtlpriv->efuse.crystalcap;

	rtlpriv->dm.atc_status = rtl_get_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11));
	rtlpriv->dm.cfo_threshold = CFO_THRESHOLD_XTAL;
}