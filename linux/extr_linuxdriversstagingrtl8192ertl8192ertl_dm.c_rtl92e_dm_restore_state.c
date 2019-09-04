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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ rate_adaptive_disabled; int /*<<< orphan*/  last_ratr; } ;
struct r8192_priv {scalar_t__ rf_type; scalar_t__ btxpower_tracking; scalar_t__ btxpower_trackingInit; TYPE_1__* rtllib; TYPE_2__ rate_adaptive; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RATE ; 
 int /*<<< orphan*/  RATE_ALL_OFDM_2SS ; 
 int /*<<< orphan*/  RATR0 ; 
 scalar_t__ RF_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UFWP ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 scalar_t__ WIRELESS_MODE_N_5G ; 
 int /*<<< orphan*/  _rtl92e_dm_bb_initialgain_restore (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_tx_power_reset_recovery (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_dm_restore_state(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	u32	reg_ratr = priv->rate_adaptive.last_ratr;
	u32 ratr_value;

	if (!priv->up) {
		RT_TRACE(COMP_RATE,
			 "<---- rtl92e_dm_restore_state(): driver is going to unload\n");
		return;
	}

	if (priv->rate_adaptive.rate_adaptive_disabled)
		return;
	if (!(priv->rtllib->mode == WIRELESS_MODE_N_24G ||
	      priv->rtllib->mode == WIRELESS_MODE_N_5G))
		return;
	ratr_value = reg_ratr;
	if (priv->rf_type == RF_1T2R)
		ratr_value &= ~(RATE_ALL_OFDM_2SS);
	rtl92e_writel(dev, RATR0, ratr_value);
	rtl92e_writeb(dev, UFWP, 1);
	if (priv->btxpower_trackingInit && priv->btxpower_tracking)
		_rtl92e_dm_tx_power_reset_recovery(dev);

	_rtl92e_dm_bb_initialgain_restore(dev);

}