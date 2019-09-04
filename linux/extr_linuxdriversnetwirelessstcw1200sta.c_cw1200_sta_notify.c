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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  drv_priv; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_sta_priv {int /*<<< orphan*/  link_id; } ;
struct cw1200_common {int /*<<< orphan*/  ps_state_lock; } ;
typedef  enum sta_notify_cmd { ____Placeholder_sta_notify_cmd } sta_notify_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  __cw1200_sta_notify (struct ieee80211_hw*,struct ieee80211_vif*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cw1200_sta_notify(struct ieee80211_hw *dev,
		       struct ieee80211_vif *vif,
		       enum sta_notify_cmd notify_cmd,
		       struct ieee80211_sta *sta)
{
	struct cw1200_common *priv = dev->priv;
	struct cw1200_sta_priv *sta_priv =
		(struct cw1200_sta_priv *)&sta->drv_priv;

	spin_lock_bh(&priv->ps_state_lock);
	__cw1200_sta_notify(dev, vif, notify_cmd, sta_priv->link_id);
	spin_unlock_bh(&priv->ps_state_lock);
}