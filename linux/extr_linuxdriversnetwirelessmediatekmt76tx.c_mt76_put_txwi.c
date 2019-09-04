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
struct mt76_txwi_cache {int /*<<< orphan*/  list; } ;
struct mt76_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  txwi_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
mt76_put_txwi(struct mt76_dev *dev, struct mt76_txwi_cache *t)
{
	if (!t)
		return;

	spin_lock_bh(&dev->lock);
	list_add(&t->list, &dev->txwi_cache);
	spin_unlock_bh(&dev->lock);
}