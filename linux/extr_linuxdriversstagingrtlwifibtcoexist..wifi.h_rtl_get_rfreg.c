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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct ieee80211_hw {struct rtl_priv* priv; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_rfreg ) (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 rtl_get_rfreg(struct ieee80211_hw *hw,
				enum radio_path rfpath, u32 regaddr,
				u32 bitmask)
{
	struct rtl_priv *rtlpriv = hw->priv;

	return rtlpriv->cfg->ops->get_rfreg(hw, rfpath, regaddr, bitmask);
}