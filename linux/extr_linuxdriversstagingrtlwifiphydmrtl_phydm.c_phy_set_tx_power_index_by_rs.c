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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int /*<<< orphan*/  hw; TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {void (* set_tx_power_index_by_rs ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phy_set_tx_power_index_by_rs(void *adapter, u8 ch, u8 path, u8 rs)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)adapter;

	return rtlpriv->cfg->ops->set_tx_power_index_by_rs(rtlpriv->hw, ch,
							   path, rs);
}