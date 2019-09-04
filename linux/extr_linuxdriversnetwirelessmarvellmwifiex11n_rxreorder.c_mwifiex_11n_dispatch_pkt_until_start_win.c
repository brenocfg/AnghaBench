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
struct mwifiex_rx_reorder_tbl {int start_win; int win_size; int /*<<< orphan*/ ** rx_reorder_ptr; } ;
struct mwifiex_private {int /*<<< orphan*/  rx_reorder_tbl_lock; } ;

/* Variables and functions */
 int min (int,int) ; 
 int /*<<< orphan*/  mwifiex_11n_dispatch_pkt (struct mwifiex_private*,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mwifiex_11n_dispatch_pkt_until_start_win(struct mwifiex_private *priv,
					 struct mwifiex_rx_reorder_tbl *tbl,
					 int start_win)
{
	int pkt_to_send, i;
	void *rx_tmp_ptr;
	unsigned long flags;

	pkt_to_send = (start_win > tbl->start_win) ?
		      min((start_win - tbl->start_win), tbl->win_size) :
		      tbl->win_size;

	for (i = 0; i < pkt_to_send; ++i) {
		spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
		rx_tmp_ptr = NULL;
		if (tbl->rx_reorder_ptr[i]) {
			rx_tmp_ptr = tbl->rx_reorder_ptr[i];
			tbl->rx_reorder_ptr[i] = NULL;
		}
		spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);
		if (rx_tmp_ptr)
			mwifiex_11n_dispatch_pkt(priv, rx_tmp_ptr);
	}

	spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
	/*
	 * We don't have a circular buffer, hence use rotation to simulate
	 * circular buffer
	 */
	for (i = 0; i < tbl->win_size - pkt_to_send; ++i) {
		tbl->rx_reorder_ptr[i] = tbl->rx_reorder_ptr[pkt_to_send + i];
		tbl->rx_reorder_ptr[pkt_to_send + i] = NULL;
	}

	tbl->start_win = start_win;
	spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);
}