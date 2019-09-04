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
typedef  int u32 ;
struct r8192_priv {int /*<<< orphan*/  txpower_tracking_wq; int /*<<< orphan*/  priv_wq; int /*<<< orphan*/  btxpower_tracking; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_CheckTXPowerTracking_TSSI(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	static u32 tx_power_track_counter;

	if (!priv->btxpower_tracking)
		return;
	if ((tx_power_track_counter % 30 == 0) && (tx_power_track_counter != 0))
		queue_delayed_work(priv->priv_wq, &priv->txpower_tracking_wq, 0);
	tx_power_track_counter++;
}