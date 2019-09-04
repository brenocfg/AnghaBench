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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct wilc {int /*<<< orphan*/  txq_spinlock; TYPE_1__ txq_head; } ;
struct txq_entry_t {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct txq_entry_t* list_next_entry (struct txq_entry_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct txq_entry_t *wilc_wlan_txq_get_next(struct wilc *wilc,
						  struct txq_entry_t *tqe)
{
	unsigned long flags;

	spin_lock_irqsave(&wilc->txq_spinlock, flags);

	if (!list_is_last(&tqe->list, &wilc->txq_head.list))
		tqe = list_next_entry(tqe, list);
	else
		tqe = NULL;
	spin_unlock_irqrestore(&wilc->txq_spinlock, flags);

	return tqe;
}