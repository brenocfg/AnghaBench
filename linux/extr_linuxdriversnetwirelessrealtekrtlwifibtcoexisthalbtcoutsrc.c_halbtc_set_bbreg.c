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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_set_bbreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtc_set_bbreg(void *bt_context, u32 reg_addr, u32 bit_mask,
			     u32 data)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)bt_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_set_bbreg(rtlpriv->mac80211.hw, reg_addr, bit_mask, data);
}