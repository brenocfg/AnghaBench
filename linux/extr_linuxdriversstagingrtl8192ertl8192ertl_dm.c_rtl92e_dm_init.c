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
struct r8192_priv {int undecorated_smoothed_pwdb; int /*<<< orphan*/  gpio_change_rf_wq; int /*<<< orphan*/  DM_Type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_Type_ByDriver ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK_RSL (int /*<<< orphan*/ *,void*,struct net_device*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8192SE (struct net_device*) ; 
 scalar_t__ _rtl92e_dm_check_rf_ctrl_gpio ; 
 int /*<<< orphan*/  _rtl92e_dm_dig_init (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_init_bandwidth_autoswitch (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_init_cts_to_self (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_init_dynamic_tx_power (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_init_fsync (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_init_rx_path_selection (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_init_wa_broadcom_iot (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_dm_init_edca_turbo (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_init_adaptive_rate (struct net_device*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_dm_init(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	priv->DM_Type = DM_Type_ByDriver;

	priv->undecorated_smoothed_pwdb = -1;

	_rtl92e_dm_init_dynamic_tx_power(dev);

	rtl92e_init_adaptive_rate(dev);

	_rtl92e_dm_dig_init(dev);
	rtl92e_dm_init_edca_turbo(dev);
	_rtl92e_dm_init_bandwidth_autoswitch(dev);
	_rtl92e_dm_init_fsync(dev);
	_rtl92e_dm_init_rx_path_selection(dev);
	_rtl92e_dm_init_cts_to_self(dev);
	if (IS_HARDWARE_TYPE_8192SE(dev))
		_rtl92e_dm_init_wa_broadcom_iot(dev);

	INIT_DELAYED_WORK_RSL(&priv->gpio_change_rf_wq,
			      (void *)_rtl92e_dm_check_rf_ctrl_gpio, dev);
}