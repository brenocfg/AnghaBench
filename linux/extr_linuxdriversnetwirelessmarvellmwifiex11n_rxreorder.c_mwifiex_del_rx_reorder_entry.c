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
struct TYPE_3__ {int timer_is_set; int /*<<< orphan*/  timer; } ;
struct mwifiex_rx_reorder_tbl {int start_win; int win_size; struct mwifiex_rx_reorder_tbl* rx_reorder_ptr; int /*<<< orphan*/  list; TYPE_1__ timer_context; } ;
struct mwifiex_private {TYPE_2__* adapter; int /*<<< orphan*/  rx_reorder_tbl_lock; } ;
struct TYPE_4__ {int rx_locked; int /*<<< orphan*/  rx_proc_lock; int /*<<< orphan*/  rx_workqueue; scalar_t__ rx_processing; } ;

/* Variables and functions */
 int MAX_TID_VALUE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_rx_reorder_tbl*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_11n_dispatch_pkt_until_start_win (struct mwifiex_private*,struct mwifiex_rx_reorder_tbl*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mwifiex_del_rx_reorder_entry(struct mwifiex_private *priv,
			     struct mwifiex_rx_reorder_tbl *tbl)
{
	unsigned long flags;
	int start_win;

	if (!tbl)
		return;

	spin_lock_irqsave(&priv->adapter->rx_proc_lock, flags);
	priv->adapter->rx_locked = true;
	if (priv->adapter->rx_processing) {
		spin_unlock_irqrestore(&priv->adapter->rx_proc_lock, flags);
		flush_workqueue(priv->adapter->rx_workqueue);
	} else {
		spin_unlock_irqrestore(&priv->adapter->rx_proc_lock, flags);
	}

	start_win = (tbl->start_win + tbl->win_size) & (MAX_TID_VALUE - 1);
	mwifiex_11n_dispatch_pkt_until_start_win(priv, tbl, start_win);

	del_timer_sync(&tbl->timer_context.timer);
	tbl->timer_context.timer_is_set = false;

	spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
	list_del(&tbl->list);
	spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);

	kfree(tbl->rx_reorder_ptr);
	kfree(tbl);

	spin_lock_irqsave(&priv->adapter->rx_proc_lock, flags);
	priv->adapter->rx_locked = false;
	spin_unlock_irqrestore(&priv->adapter->rx_proc_lock, flags);

}