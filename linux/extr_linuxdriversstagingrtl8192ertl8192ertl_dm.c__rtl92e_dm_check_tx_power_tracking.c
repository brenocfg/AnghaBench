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
struct r8192_priv {scalar_t__ IC_Cut; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IC_VersionCut_D ; 
 int /*<<< orphan*/  _rtl92e_dm_check_tx_power_tracking_thermal (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_check_tx_power_tracking_tssi (struct net_device*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_check_tx_power_tracking(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (priv->IC_Cut >= IC_VersionCut_D)
		_rtl92e_dm_check_tx_power_tracking_tssi(dev);
	else
		_rtl92e_dm_check_tx_power_tracking_thermal(dev);
}