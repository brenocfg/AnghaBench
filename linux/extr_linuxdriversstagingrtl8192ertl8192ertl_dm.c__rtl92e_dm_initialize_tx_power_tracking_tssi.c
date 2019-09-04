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
struct r8192_priv {int btxpower_tracking; int btxpower_trackingInit; scalar_t__ txpower_count; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_initialize_tx_power_tracking_tssi(struct net_device *dev)
{

	struct r8192_priv *priv = rtllib_priv(dev);

	priv->btxpower_tracking = true;
	priv->txpower_count       = 0;
	priv->btxpower_trackingInit = false;

}