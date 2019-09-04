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
struct mwifiex_rx_reorder_tbl {int win_size; int start_win; int /*<<< orphan*/ ** rx_reorder_ptr; } ;
struct mwifiex_private {int /*<<< orphan*/  rx_reorder_tbl_lock; } ;

/* Variables and functions */
 int MAX_TID_VALUE ; 
 int /*<<< orphan*/  mwifiex_11n_dispatch_pkt (struct mwifiex_private*,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mwifiex_11n_scan_and_dispatch(struct mwifiex_private *priv,
			      struct mwifiex_rx_reorder_tbl *tbl)
{
	int i, j, xchg;
	void *rx_tmp_ptr;
	unsigned long flags;

	for (i = 0; i < tbl->win_size; ++i) {
		spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
		if (!tbl->rx_reorder_ptr[i]) {
			spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock,
					       flags);
			break;
		}
		rx_tmp_ptr = tbl->rx_reorder_ptr[i];
		tbl->rx_reorder_ptr[i] = NULL;
		spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);
		mwifiex_11n_dispatch_pkt(priv, rx_tmp_ptr);
	}

	spin_lock_irqsave(&priv->rx_reorder_tbl_lock, flags);
	/*
	 * We don't have a circular buffer, hence use rotation to simulate
	 * circular buffer
	 */
	if (i > 0) {
		xchg = tbl->win_size - i;
		for (j = 0; j < xchg; ++j) {
			tbl->rx_reorder_ptr[j] = tbl->rx_reorder_ptr[i + j];
			tbl->rx_reorder_ptr[i + j] = NULL;
		}
	}
	tbl->start_win = (tbl->start_win + i) & (MAX_TID_VALUE - 1);
	spin_unlock_irqrestore(&priv->rx_reorder_tbl_lock, flags);
}