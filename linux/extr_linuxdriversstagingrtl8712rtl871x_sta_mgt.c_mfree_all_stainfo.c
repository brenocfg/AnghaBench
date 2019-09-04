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
struct list_head {struct list_head* next; } ;
struct TYPE_2__ {struct list_head queue; } ;
struct sta_priv {int /*<<< orphan*/  sta_hash_lock; TYPE_1__ free_sta_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_of_queue_search (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mfree_all_stainfo(struct sta_priv *pstapriv)
{
	unsigned long irqL;
	struct list_head *plist, *phead;

	spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
	phead = &pstapriv->free_sta_queue.queue;
	plist = phead->next;
	while (!end_of_queue_search(phead, plist))
		plist = plist->next;

	spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
}