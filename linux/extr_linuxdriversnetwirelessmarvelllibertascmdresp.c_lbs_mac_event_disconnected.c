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
struct lbs_private {scalar_t__ connect_status; scalar_t__ psstate; int /*<<< orphan*/  driver_lock; scalar_t__ tx_pending_len; int /*<<< orphan*/ * currenttxskb; int /*<<< orphan*/  dev; TYPE_1__* wdev; } ;
struct TYPE_2__ {scalar_t__ iftype; } ;

/* Variables and functions */
 scalar_t__ LBS_CONNECTED ; 
 scalar_t__ LBS_DISCONNECTED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PS_MODE_ACTION_EXIT_PS ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*) ; 
 int /*<<< orphan*/  lbs_send_disconnect_notification (struct lbs_private*,int) ; 
 int /*<<< orphan*/  lbs_set_ps_mode (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void lbs_mac_event_disconnected(struct lbs_private *priv,
				bool locally_generated)
{
	unsigned long flags;

	if (priv->connect_status != LBS_CONNECTED)
		return;

	/*
	 * Cisco AP sends EAP failure and de-auth in less than 0.5 ms.
	 * It causes problem in the Supplicant
	 */
	msleep_interruptible(1000);

	if (priv->wdev->iftype == NL80211_IFTYPE_STATION)
		lbs_send_disconnect_notification(priv, locally_generated);

	/* report disconnect to upper layer */
	netif_stop_queue(priv->dev);
	netif_carrier_off(priv->dev);

	/* Free Tx and Rx packets */
	spin_lock_irqsave(&priv->driver_lock, flags);
	kfree_skb(priv->currenttxskb);
	priv->currenttxskb = NULL;
	priv->tx_pending_len = 0;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	priv->connect_status = LBS_DISCONNECTED;

	if (priv->psstate != PS_STATE_FULL_POWER) {
		/* make firmware to exit PS mode */
		lbs_deb_cmd("disconnected, so exit PS mode\n");
		lbs_set_ps_mode(priv, PS_MODE_ACTION_EXIT_PS, false);
	}
}