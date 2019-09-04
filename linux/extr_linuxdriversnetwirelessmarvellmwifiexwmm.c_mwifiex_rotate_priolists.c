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
struct mwifiex_tid_tbl {int /*<<< orphan*/  ra_list; } ;
struct mwifiex_ra_list_tbl {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  ra_list_spinlock; int /*<<< orphan*/ * packets_out; struct mwifiex_tid_tbl* tid_tbl_ptr; } ;
struct mwifiex_private {size_t bss_priority; TYPE_2__ wmm; struct mwifiex_adapter* adapter; } ;
struct mwifiex_bss_prio_tbl {int /*<<< orphan*/  bss_prio_lock; TYPE_1__* bss_prio_cur; int /*<<< orphan*/  bss_prio_head; } ;
struct mwifiex_adapter {struct mwifiex_bss_prio_tbl* bss_prio_tbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mwifiex_is_ralist_valid (struct mwifiex_private*,struct mwifiex_ra_list_tbl*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mwifiex_rotate_priolists(struct mwifiex_private *priv,
				 struct mwifiex_ra_list_tbl *ra,
				 int tid)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_bss_prio_tbl *tbl = adapter->bss_prio_tbl;
	struct mwifiex_tid_tbl *tid_ptr = &priv->wmm.tid_tbl_ptr[tid];
	unsigned long flags;

	spin_lock_irqsave(&tbl[priv->bss_priority].bss_prio_lock, flags);
	/*
	 * dirty trick: we remove 'head' temporarily and reinsert it after
	 * curr bss node. imagine list to stay fixed while head is moved
	 */
	list_move(&tbl[priv->bss_priority].bss_prio_head,
		  &tbl[priv->bss_priority].bss_prio_cur->list);
	spin_unlock_irqrestore(&tbl[priv->bss_priority].bss_prio_lock, flags);

	spin_lock_irqsave(&priv->wmm.ra_list_spinlock, flags);
	if (mwifiex_is_ralist_valid(priv, ra, tid)) {
		priv->wmm.packets_out[tid]++;
		/* same as above */
		list_move(&tid_ptr->ra_list, &ra->list);
	}
	spin_unlock_irqrestore(&priv->wmm.ra_list_spinlock, flags);
}