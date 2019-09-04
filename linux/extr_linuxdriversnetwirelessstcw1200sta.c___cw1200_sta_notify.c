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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_common {int link_id_map; int sta_asleep_mask; int pspoll_mask; int /*<<< orphan*/  multicast_stop_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  multicast_start_work; int /*<<< orphan*/  buffered_multicasts; } ;
typedef  enum sta_notify_cmd { ____Placeholder_sta_notify_cmd } sta_notify_cmd ;

/* Variables and functions */
 int BIT (int) ; 
#define  STA_NOTIFY_AWAKE 129 
#define  STA_NOTIFY_SLEEP 128 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cw1200_bh_wakeup (struct cw1200_common*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cw1200_sta_notify(struct ieee80211_hw *dev,
				struct ieee80211_vif *vif,
				enum sta_notify_cmd notify_cmd,
				int link_id)
{
	struct cw1200_common *priv = dev->priv;
	u32 bit, prev;

	/* Zero link id means "for all link IDs" */
	if (link_id)
		bit = BIT(link_id);
	else if (WARN_ON_ONCE(notify_cmd != STA_NOTIFY_AWAKE))
		bit = 0;
	else
		bit = priv->link_id_map;
	prev = priv->sta_asleep_mask & bit;

	switch (notify_cmd) {
	case STA_NOTIFY_SLEEP:
		if (!prev) {
			if (priv->buffered_multicasts &&
			    !priv->sta_asleep_mask)
				queue_work(priv->workqueue,
					   &priv->multicast_start_work);
			priv->sta_asleep_mask |= bit;
		}
		break;
	case STA_NOTIFY_AWAKE:
		if (prev) {
			priv->sta_asleep_mask &= ~bit;
			priv->pspoll_mask &= ~bit;
			if (priv->tx_multicast && link_id &&
			    !priv->sta_asleep_mask)
				queue_work(priv->workqueue,
					   &priv->multicast_stop_work);
			cw1200_bh_wakeup(priv);
		}
		break;
	}
}