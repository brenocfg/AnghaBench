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
struct wiphy {int dummy; } ;
struct wilc_vif {TYPE_1__* wilc; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;
struct cfg80211_wowlan {int dummy; } ;
struct TYPE_2__ {int suspend_event; } ;

/* Variables and functions */
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ wilc_wlan_get_num_conn_ifcs (TYPE_1__*) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int wilc_suspend(struct wiphy *wiphy, struct cfg80211_wowlan *wow)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	if (!wow && wilc_wlan_get_num_conn_ifcs(vif->wilc))
		vif->wilc->suspend_event = true;
	else
		vif->wilc->suspend_event = false;

	return 0;
}