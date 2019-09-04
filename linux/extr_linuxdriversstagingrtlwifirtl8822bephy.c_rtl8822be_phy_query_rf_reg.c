#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  rf_lock; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct rtl_priv {TYPE_1__ locks; TYPE_3__ phydm; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
struct TYPE_5__ {int /*<<< orphan*/  (* phydm_read_rf_reg ) (struct rtl_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 rtl8822be_phy_query_rf_reg(struct ieee80211_hw *hw, enum radio_path rfpath,
			       u32 regaddr, u32 bitmask)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 /*original_value,*/ readback_value /*, bitshift*/;
	unsigned long flags;

	RT_TRACE(rtlpriv, COMP_RF, DBG_TRACE,
		 "regaddr(%#x), rfpath(%#x), bitmask(%#x)\n", regaddr, rfpath,
		 bitmask);

	spin_lock_irqsave(&rtlpriv->locks.rf_lock, flags);

	readback_value = rtlpriv->phydm.ops->phydm_read_rf_reg(
		rtlpriv, rfpath, regaddr, bitmask);

	spin_unlock_irqrestore(&rtlpriv->locks.rf_lock, flags);

	return readback_value;
}