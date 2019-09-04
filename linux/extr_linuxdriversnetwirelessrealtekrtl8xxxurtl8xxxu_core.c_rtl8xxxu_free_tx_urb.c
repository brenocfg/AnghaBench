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
struct rtl8xxxu_tx_urb {int /*<<< orphan*/  list; } ;
struct rtl8xxxu_priv {scalar_t__ tx_urb_free_count; int tx_stopped; int /*<<< orphan*/  tx_urb_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_urb_free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ RTL8XXXU_TX_URB_HIGH_WATER ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtl8xxxu_free_tx_urb(struct rtl8xxxu_priv *priv,
				 struct rtl8xxxu_tx_urb *tx_urb)
{
	unsigned long flags;

	INIT_LIST_HEAD(&tx_urb->list);

	spin_lock_irqsave(&priv->tx_urb_lock, flags);

	list_add(&tx_urb->list, &priv->tx_urb_free_list);
	priv->tx_urb_free_count++;
	if (priv->tx_urb_free_count > RTL8XXXU_TX_URB_HIGH_WATER &&
	    priv->tx_stopped) {
		priv->tx_stopped = false;
		ieee80211_wake_queues(priv->hw);
	}

	spin_unlock_irqrestore(&priv->tx_urb_lock, flags);
}