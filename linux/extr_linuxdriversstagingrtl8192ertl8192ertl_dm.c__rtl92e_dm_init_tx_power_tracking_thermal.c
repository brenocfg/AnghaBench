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
struct r8192_priv {int btxpower_tracking; int btxpower_trackingInit; scalar_t__ txpower_count; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ FwRWRF; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_init_tx_power_tracking_thermal(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);


	if (priv->rtllib->FwRWRF)
		priv->btxpower_tracking = true;
	else
		priv->btxpower_tracking = false;
	priv->txpower_count       = 0;
	priv->btxpower_trackingInit = false;
	RT_TRACE(COMP_POWER_TRACKING, "pMgntInfo->bTXPowerTracking = %d\n",
		 priv->btxpower_tracking);
}