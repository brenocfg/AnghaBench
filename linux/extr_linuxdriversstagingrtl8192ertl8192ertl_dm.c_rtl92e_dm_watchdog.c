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
struct r8192_priv {scalar_t__ being_init_adapter; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92e_dm_bandwidth_autoswitch (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_ac_dc_power (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_edca_turbo (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_fsync (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_rate_adaptive (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_rx_path_selection (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_tx_power_tracking (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_txrateandretrycount (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_ctrl_initgain_byrssi (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_cts_to_self (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_dynamic_tx_power (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_send_rssi_to_fw (struct net_device*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_dm_watchdog(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (priv->being_init_adapter)
		return;

	_rtl92e_dm_check_ac_dc_power(dev);

	_rtl92e_dm_check_txrateandretrycount(dev);
	_rtl92e_dm_check_edca_turbo(dev);

	_rtl92e_dm_check_rate_adaptive(dev);
	_rtl92e_dm_dynamic_tx_power(dev);
	_rtl92e_dm_check_tx_power_tracking(dev);

	_rtl92e_dm_ctrl_initgain_byrssi(dev);
	_rtl92e_dm_bandwidth_autoswitch(dev);

	_rtl92e_dm_check_rx_path_selection(dev);
	_rtl92e_dm_check_fsync(dev);

	_rtl92e_dm_send_rssi_to_fw(dev);
	_rtl92e_dm_cts_to_self(dev);
}