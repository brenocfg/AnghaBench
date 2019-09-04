#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * pfirmware; } ;
struct TYPE_9__ {TYPE_3__* ops; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_5__ rtlhal; TYPE_4__ phydm; TYPE_2__ halmac; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* phydm_deinit_priv ) (struct rtl_priv*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* halmac_deinit_adapter ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void rtl8822be_deinit_sw_vars(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->halmac.ops->halmac_deinit_adapter(rtlpriv);
	rtlpriv->phydm.ops->phydm_deinit_priv(rtlpriv);

	if (rtlpriv->rtlhal.pfirmware) {
		vfree(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = NULL;
	}
}