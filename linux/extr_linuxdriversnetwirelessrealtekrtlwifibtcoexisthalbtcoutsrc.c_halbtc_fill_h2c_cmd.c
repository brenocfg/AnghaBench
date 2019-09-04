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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct rtl_priv {TYPE_3__ mac80211; TYPE_2__* cfg; } ;
struct btc_coexist {struct rtl_priv* adapter; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fill_h2c_cmd ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halbtc_fill_h2c_cmd(void *bt_context, u8 element_id,
				u32 cmd_len, u8 *cmd_buf)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)bt_context;
	struct rtl_priv *rtlpriv = btcoexist->adapter;

	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->mac80211.hw, element_id,
					cmd_len, cmd_buf);
}