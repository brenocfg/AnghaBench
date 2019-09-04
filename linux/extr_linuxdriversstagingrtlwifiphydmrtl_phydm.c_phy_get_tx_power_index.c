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
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_txpower_index ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

u8 phy_get_tx_power_index(void *adapter, u8 rf_path, u8 rate,
			  enum ht_channel_width bandwidth, u8 channel)
{
	/* rate: DESC_RATE1M */
	struct rtl_priv *rtlpriv = (struct rtl_priv *)adapter;

	return rtlpriv->cfg->ops->get_txpower_index(rtlpriv->hw, rf_path, rate,
						    bandwidth, channel);
}