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
struct r8192_priv {int /*<<< orphan*/  update_beacon_wq; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {int dummy; } ;
struct ieee80211_beacon {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_qos_handle_probe_response (struct r8192_priv*,int,struct ieee80211_network*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8192_handle_beacon(struct net_device *dev,
				 struct ieee80211_beacon *beacon,
				 struct ieee80211_network *network)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	rtl8192_qos_handle_probe_response(priv, 1, network);
	schedule_delayed_work(&priv->update_beacon_wq, 0);
	return 0;
}