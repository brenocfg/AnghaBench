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
typedef  int /*<<< orphan*/  u32 ;
struct wifi_only_cfg {scalar_t__ adapter; } ;
struct rtl_priv {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_set_bbreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void halwifionly_phy_set_bb_reg(struct wifi_only_cfg *wifi_conly_cfg,
				u32 regaddr, u32 bitmask, u32 data)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)wifi_conly_cfg->adapter;

	rtl_set_bbreg(rtlpriv->hw, regaddr, bitmask, data);
}