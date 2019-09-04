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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct wilc_vif {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct cfg80211_beacon_data {scalar_t__ tail; int /*<<< orphan*/  tail_len; scalar_t__ head; int /*<<< orphan*/  head_len; } ;

/* Variables and functions */
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_add_beacon (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int change_beacon(struct wiphy *wiphy, struct net_device *dev,
			 struct cfg80211_beacon_data *beacon)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	return wilc_add_beacon(vif, 0, 0, beacon->head_len,
				   (u8 *)beacon->head, beacon->tail_len,
				   (u8 *)beacon->tail);
}