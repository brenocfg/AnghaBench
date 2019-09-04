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
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  probe_work; int /*<<< orphan*/  lock; int /*<<< orphan*/ * req; } ;
struct cw1200_common {int listening; int join_pending; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  join_status; int /*<<< orphan*/  event_queue_lock; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  mode; int /*<<< orphan*/  mcast_timeout; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  link_id_gc_work; int /*<<< orphan*/  unjoin_work; int /*<<< orphan*/  join_timeout; int /*<<< orphan*/  clear_recent_scan_work; TYPE_1__ scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CW1200_JOIN_STATUS_PASSIVE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  __cw1200_free_event_queue (int /*<<< orphan*/ *) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_cqm_bssloss_sm (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cw1200_queue_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_policy_clean (struct cw1200_common*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_lock_tx (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

void cw1200_stop(struct ieee80211_hw *dev)
{
	struct cw1200_common *priv = dev->priv;
	LIST_HEAD(list);
	int i;

	wsm_lock_tx(priv);

	while (down_trylock(&priv->scan.lock)) {
		/* Scan is in progress. Force it to stop. */
		priv->scan.req = NULL;
		schedule();
	}
	up(&priv->scan.lock);

	cancel_delayed_work_sync(&priv->scan.probe_work);
	cancel_delayed_work_sync(&priv->scan.timeout);
	cancel_delayed_work_sync(&priv->clear_recent_scan_work);
	cancel_delayed_work_sync(&priv->join_timeout);
	cw1200_cqm_bssloss_sm(priv, 0, 0, 0);
	cancel_work_sync(&priv->unjoin_work);
	cancel_delayed_work_sync(&priv->link_id_gc_work);
	flush_workqueue(priv->workqueue);
	del_timer_sync(&priv->mcast_timeout);
	mutex_lock(&priv->conf_mutex);
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->listening = false;

	spin_lock(&priv->event_queue_lock);
	list_splice_init(&priv->event_queue, &list);
	spin_unlock(&priv->event_queue_lock);
	__cw1200_free_event_queue(&list);


	priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
	priv->join_pending = false;

	for (i = 0; i < 4; i++)
		cw1200_queue_clear(&priv->tx_queue[i]);
	mutex_unlock(&priv->conf_mutex);
	tx_policy_clean(priv);

	/* HACK! */
	if (atomic_xchg(&priv->tx_lock, 1) != 1)
		pr_debug("[STA] TX is force-unlocked due to stop request.\n");

	wsm_unlock_tx(priv);
	atomic_xchg(&priv->tx_lock, 0); /* for recovery to work */
}