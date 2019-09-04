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
struct phy_dm_struct {scalar_t__ adapter; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_set_txpower_limit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void phy_set_tx_power_limit(void *dm, u8 *regulation, u8 *band, u8 *bandwidth,
			    u8 *rate_section, u8 *rf_path, u8 *channel,
			    u8 *power_limit)
{
	struct rtl_priv *rtlpriv =
		(struct rtl_priv *)((struct phy_dm_struct *)dm)->adapter;

	rtlpriv->cfg->ops->phy_set_txpower_limit(rtlpriv->hw, regulation, band,
						 bandwidth, rate_section,
						 rf_path, channel, power_limit);
}